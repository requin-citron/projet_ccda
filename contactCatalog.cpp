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

void ContactCatalog::addContact(std::string firstName, std::string lastName, std::string enterprise, std::string mail, std::string phone, std::string pathPicture){
  Contact *c = new Contact(firstName, lastName, enterprise, mail, phone, pathPicture, &(this->tag_lst));
  this->local_hist->insertHist(c,CREATE_CONTACT);
  this->contact_lst.push_back(c);
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
    QString lst[] = {"contacts", "interactions", "tags", "history_contact", "history_interaction"};
    for(int i=0; i < 5; i++){
        query.prepare("DELETE FROM "+lst[i]+";");
        if(!query.exec()){
            qWarning() << "Error: " << query.lastError().text();
            exit(1);
        }
    }
}

void ContactCatalog::saveDataBase(){
    const QString DRIVER("QSQLITE");
    if(!QSqlDatabase::isDriverAvailable(DRIVER)){
        qWarning() << "Error: SQL DRIVER unavailable";
        exit(1);
    }
    QSqlDatabase db =  QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName(DATABASE_NAME);
    if(!db.open()){
        qWarning() << "Error: " << db.lastError();
        exit(1);
    }
    //clean database
    this->cleanDataBase();

    QSqlQuery query;
    //mais quelle bonne idée de faire toute la premiere partie sans les types QT
    //vraiment on aime
    QVariant id;
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
    }

    db.close();
}
