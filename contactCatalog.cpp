#include "contactCatalog.hpp"

ContactCatalog::ContactCatalog(){
  this->local_hist = new HistLocal();
}

ContactCatalog::~ContactCatalog(){
  delete this->local_hist;
  for(auto &it: this->contact_lst){
    delete it;
  }
}

Contact* ContactCatalog::addContact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture){
  Contact *c = new Contact(firstName, lastName, enterprise, mail, phone, pathPicture, &(this->tag_lst));
  this->local_hist->insertHist(c,CREATE_CONTACT);
  this->contact_lst.push_back(c);
  return c;
}

std::list<Contact*>* ContactCatalog::getContactLst(){
  return &(this->contact_lst);
}

HistLocal *ContactCatalog::getHist(){
  return this->local_hist;
}

void ContactCatalog::eraseContact(Contact *c){
  this->local_hist->insertHist(c,DELETE_CONTACT);
  delete c;
  this->contact_lst.remove(c);
}

void ContactCatalog::cleanDataBase(){
    QSqlQuery query;
    QString lst[] = {"contacts", "interactions", "tags", "history_contact", "history_interaction","history_global"};
    for(int i=0; i < 6; i++){
        query.prepare("DELETE FROM "+lst[i]+";");
        if(!query.exec()){
            qWarning() << "Error: " << query.lastError().text();
            exit(1);
        }
    }
}

void ContactCatalog::initDbConnexion(){
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)){
        qWarning() << "Error: SQL DRIVER unavailable";
        exit(1);
    }
    this->db =  QSqlDatabase::addDatabase(DRIVER);
    this->db.setDatabaseName(DATABASE_NAME);
    if(!this->db.open()){
        qWarning() << "Error: " << this->db.lastError();
        exit(1);
    }
}

void ContactCatalog::eraseDbConnexion(){
    const QString name = this->db.connectionName();
    this->db.close();
    //QSqlDatabase::removeDatabase(name);
}

void ContactCatalog::saveDataBase(){
    this->initDbConnexion();
    //clean database
    this->cleanDataBase();
    QSqlQuery query;
    // historique global
    for(auto &it: *this->local_hist->getLst()){
        query.prepare("INSERT INTO history_global (contenue, dt) "
                      "VALUES (:contenue, :dt)");
        query.bindValue(":contenue", QString::fromStdString(it->first));
        query.bindValue(":dt",QString::fromStdString(it->second.print()));
        if(!query.exec()){
            qWarning() << "Error: " << query.lastError().text();
            exit(1);
        }
    }
    //contact interaction historique locaux
    QVariant id;
    QVariant id_inte;
    //contact
    for(auto &it: this->contact_lst){
        id.setValue(it->getId());
        query.prepare("INSERT INTO contacts (id, email, first_name, last_name, enterprise, phone, photo) "
                      "VALUES (:id, :email, :first_name, :last_name, :enterprise, :phone, :photo)");
        query.bindValue(":id", id);
        query.bindValue(":email",QString::fromStdString(it->getMail()));
        query.bindValue(":first_name", QString::fromStdString(it->getFirstName()));
        query.bindValue(":last_name", QString::fromStdString(it->getLastName()));
        query.bindValue(":enterprise", QString::fromStdString(it->getEnterprise()));
        query.bindValue(":phone", QString::fromStdString(it->getPhone()));
        query.bindValue(":photo",QString::fromStdString(it->getPathPicture()));
        if(!query.exec()){
            qWarning() << "Error: " << query.lastError().text();
            exit(1);
        }
        //gestion des historiques
        for(auto &hist_contact: *(it->getHist()->getLst())){
            query.prepare("INSERT INTO history_contact (id_contact, contenue, dt) "
                          "VALUES (:id_contact, :contenue, :dt)");
            query.bindValue(":id_contact", id);
            query.bindValue(":contenue",QString::fromStdString(hist_contact->first));
            query.bindValue(":dt", QString::fromStdString(hist_contact->second.print()));
            if(!query.exec()){
                qWarning() << "Error: " << query.lastError().text();
                exit(1);
            }
        }
        //gestion des interaction
        for(auto &inte_local: *it->getInteractionLst()){
            query.prepare("INSERT INTO interactions (id_contact, id_interaction, contenue) "
                          "VALUES (:id_contact, :id_interaction, :contenue)");
            query.bindValue(":id_contact", id);
            id_inte.setValue(inte_local->getId());
            query.bindValue(":id_interaction",id_inte);
            query.bindValue(":contenue", QString::fromStdString(inte_local->getContenu()));
            if(!query.exec()){
                qWarning() << "Error: " << query.lastError().text();
                exit(1);
            }
            //historique local a l'interaction
            for(auto &hist_inte: *(inte_local->getHist()->getLst())){
                query.prepare("INSERT INTO history_interaction (id_contact, id_interaction, contenue, dt) "
                              "VALUES (:id_contact,:id_interaction, :contenue, :dt)");
                query.bindValue(":id_contact", id);
                query.bindValue(":id_interaction",id_inte);
                query.bindValue(":contenue", QString::fromStdString(hist_inte->first));
                query.bindValue(":dt", QString::fromStdString(hist_inte->second.print()));
                if(!query.exec()){
                    qWarning() << "Error: " << query.lastError().text();
                    exit(1);
                }
            }
            //tags
            for(auto &tag : *inte_local->getTags()){
                query.prepare("INSERT INTO tags (name,id_contact, id_interaction) "
                              "VALUES (:name, :id_contact, :id_interaction)");
                query.bindValue(":name",QString::fromStdString(tag->getName()));
                query.bindValue(":id_contact",id);
                query.bindValue(":id_interaction",id_inte);
                if(!query.exec()){
                    qWarning() << "Error: " << query.lastError().text();
                    exit(1);
                }
            }
        }
    }
    this->eraseDbConnexion();
}

void ContactCatalog::loadDataBase(){
    this->initDbConnexion();
    //importation des contacts
    QSqlQuery query;
    QSqlQuery query1;
    QSqlQuery query2;
    if(!query.exec("SELECT * FROM contacts ORDER BY id ASC;")){
        qWarning() << "Error: " << query.lastError().text();
        exit(1);
    }
    Contact *tmp = NULL;
    Interaction *inte_tmp = NULL;
    QVariant magie;
    QVariant magie1;
    while (query.next()) {
        tmp = new Contact((size_t)query.value(0).toInt(), query.value(2).toString().toStdString(),
                    query.value(3).toString().toStdString(), query.value(3).toString().toStdString(),
                    query.value(1).toString().toStdString(), query.value(5).toString().toStdString(),
                    query.value(6).toString().toStdString(),&this->tag_lst);
        // les injection sql pas pour nous
        magie.setValue(tmp->getId());
        // gestion historique
        query1.prepare("SELECT contenue, dt FROM history_contact WHERE id_contact=:chevalo;");
        query1.bindValue(":chevalo", magie);
        if(!query1.exec()){
            qWarning() << "Error: SQL DRIVER unavailable";
            exit(1);
        }
        while(query1.next()){
            tmp->getHist()->insertHist(query1.value(0).toString().toStdString(), query1.value(1).toString().toStdString());
        }
        // gestion interaction
         query1.prepare("SELECT id_interaction, contenue FROM interactions WHERE id_contact=:chevalo ORDER BY id_interaction ASC;");
         query1.bindValue(":chevalo", magie);
         if(!query1.exec()){
             qWarning() << "Error: SQL DRIVER unavailable";
             exit(1);
         }
         while(query1.next()){
             tmp->addInteraction((size_t)query1.value(0).toInt(), query1.value(1).toString().toStdString());
             inte_tmp = *(--tmp->getInteractionLst()->end());
             magie1.setValue(query1.value(0));
             //historique
             query2.prepare("SELECT contenue, dt FROM history_interaction WHERE id_contact=:id_c and id_interaction=:id_inte;");
             query2.bindValue(":id_c", magie);
             query2.bindValue(":id_inte", magie1);
             if(!query2.exec()){
                 qWarning() << "Error: SQL DRIVER unavailable";
                 exit(1);
             }

             while(query2.next()){
                 inte_tmp->getHist()->insertHist(query2.value(0).toString().toStdString(), query2.value(1).toString().toStdString());
             }
             //tag
             query2.prepare("SELECT name FROM tags WHERE id_contact=:id_c and id_interaction=:id_inte;");
             query2.bindValue(":id_c", magie);
             query2.bindValue(":id_inte", magie1);

             if(!query2.exec()){
                 qWarning() << "Error: SQL DRIVER unavailable";
                 exit(1);
             }

             while(query2.next()){
                 inte_tmp->addTagUnLog(query2.value(0).toString().toStdString());
             }

         }
         this->contact_lst.push_back(tmp);
    }
    // gestion global hist
    if(!query1.exec("SELECT contenue, dt from history_global;")){
        qWarning() << "Error: SQL DRIVER unavailable";
        exit(1);
    }
    while(query1.next()){
        this->local_hist->insertHist(query1.value(0).toString().toStdString(), query1.value(1).toString().toStdString());
    }
    this->eraseDbConnexion();
}

void ContactCatalog::saveJson(){
    QJsonObject jsonObj;
    // global array
    QJsonArray *jsonArray = new QJsonArray();
    //interaction and hist array
    QJsonArray *jsonArrayInteraction = NULL;
    // todo and tags array
    QJsonArray *jsonArrayTags = NULL;
    QByteArray byteArray;
    QJsonObject *tmp_contact = NULL;
    //aussi pour historique
    QJsonObject *tmp_interaction = NULL;
    QJsonObject *tmp_todo = NULL;
    for(auto &it:this->contact_lst){
        tmp_contact = new QJsonObject();
        jsonArrayInteraction = new QJsonArray();
        (*tmp_contact)["prenom"] = QString::fromStdString(it->getFirstName());
        (*tmp_contact)["nom"] = QString::fromStdString(it->getLastName());
        (*tmp_contact)["entreprise"] = QString::fromStdString(it->getEnterprise());
        (*tmp_contact)["mail"] = QString::fromStdString(it->getMail());
        (*tmp_contact)["phone"] = QString::fromStdString(it->getPhone());
        (*tmp_contact)["pathPicture"] = QString::fromStdString(it->getPathPicture());
        for(auto &ot: *it->getInteractionLst()){
            tmp_interaction = new QJsonObject();
            (*tmp_interaction)["contenue"] = QString::fromStdString(ot->getContenu());
            //tag loop
            jsonArrayTags = new QJsonArray();
            for(auto &lt: *ot->getTags()){
                jsonArrayTags->append(QString::fromStdString(lt->getName()));
            }
            (*tmp_interaction)["tags"] = *jsonArrayTags;
            delete  jsonArrayTags;
            //todo loop
            jsonArrayTags = new QJsonArray();
            for(auto &lt: *ot->getTodo()){
                tmp_todo = new QJsonObject();
                (*tmp_todo)["contenue"] = QString::fromStdString(lt->first);
                if(lt->second!=NULL){
                    (*tmp_todo)["date"] = QString::fromStdString(lt->second->printAll());
                }else{
                    (*tmp_todo)["date"];
                }
                jsonArrayTags->append(*tmp_todo);
                delete tmp_todo;
            }
            (*tmp_interaction)["todo"] = *jsonArrayTags;
            delete  jsonArrayTags;
            //hist loop
            jsonArrayTags = new QJsonArray();
            for(auto &lt: *ot->getHist()->getLst()){
                tmp_todo = new QJsonObject();
                (*tmp_todo)["contenue"] = QString::fromStdString(lt->first);
                (*tmp_todo)["date"] = QString::fromStdString(lt->second.printAll());
                jsonArrayTags->append(*tmp_todo);
                delete tmp_todo;
            }
            (*tmp_interaction)["historique"] = *jsonArrayTags;
            delete  jsonArrayTags;
            //fin hist
            (*jsonArrayInteraction).append(*tmp_interaction);
            delete tmp_interaction;
        }
        (*tmp_contact)["interactions"] = *jsonArrayInteraction;
        // historique
        delete jsonArrayInteraction;
        jsonArrayInteraction = new QJsonArray();
        for(auto &ot: *it->getHist()->getLst()){
            tmp_interaction = new QJsonObject();
            (*tmp_interaction)["contenue"] = QString::fromStdString(ot->first);
            (*tmp_interaction)["date"] = QString::fromStdString(ot->second.printAll());
            jsonArrayInteraction->append(*tmp_interaction);
            delete tmp_interaction;
        }
        (*tmp_contact)["historique"] = *jsonArrayInteraction;
        jsonArray->append(*tmp_contact);
        delete tmp_contact;
        delete jsonArrayInteraction;
    }
    jsonObj["contacts"] = *jsonArray;
    delete jsonArray;
    jsonArray = new QJsonArray();
    //global hist
    for(auto &it: *this->getHist()->getLst()){
       tmp_contact = new QJsonObject();
       (*tmp_contact)["contenue"] = QString::fromStdString(it->first);
       (*tmp_contact)["date"] = QString::fromStdString(it->second.printAll());
       jsonArray->append(*tmp_contact);
       delete tmp_contact;
    }
    jsonObj["historique"]=*jsonArray;
    delete jsonArray;
    byteArray = QJsonDocument(jsonObj).toJson();
    std::cout << byteArray.toStdString() << std::endl;
}
