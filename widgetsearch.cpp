#include "widgetsearch.hpp"

WidgetSearch::WidgetSearch(ContactCatalog *cata) : QWidget(){
    this->cata = cata;
    this->widgetListSearch->setStyleSheet("QListWidget {font-size: 20px;}");
    this->widgetBack->setText(tr("Retour en arrière"));
    this->widgetSuprr->setText(tr("Supprimer le tag"));
    QVBoxLayout *l1 = new QVBoxLayout;
    QHBoxLayout *l2 = new QHBoxLayout;
    l2->addWidget(this->widgetCombo);
    l2->addWidget(this->widgetSuprr);
    l1->addLayout(l2);
    l1->addWidget(this->widgetListSearch);
    l1->addWidget(this->widgetBack);
    this->setLayout(l1);
    QObject::connect(this->widgetBack,SIGNAL(clicked()), this , SLOT(handlerBack()));
   // changement dans la list deroulante
    QObject::connect(this->widgetCombo,SIGNAL(currentTextChanged(const QString&)),this, SLOT(reloadOnChange(const QString&)));
    // suppresion d'un tag
    QObject::connect(this->widgetSuprr, SIGNAL(clicked()), this, SLOT(deleteTag()));
    // double clic sur une interaction
    QObject::connect(this->widgetListSearch, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(printInter(QListWidgetItem*)));
    // la magie opere
    this->reloadSelf();
}

void WidgetSearch::handlerBack(){
    emit goBack();
}

void WidgetSearch::reloadSelf(){
    this->widgetCombo->clear();
    this->widgetCombo->addItem(DEFAULT_MESSAGE);
    for(auto &it: *this->cata->getTagList()->getTagList()){
        this->widgetCombo->addItem(QString::fromStdString(it->getName()));
    }
    this->reloadOnChange(DEFAULT_MESSAGE);

}

void WidgetSearch::reloadOnChange(const QString &text){
    // selectionne toutes les interactions
    std::string tmp = text.toStdString();
    if(text.toStdString()=="") return;
    this->widgetListSearch->clear();
    if(tmp == DEFAULT_MESSAGE){
        for(auto &it: *this->cata->getContactLst()){
            for(auto &ot: *it->getInteractionLst()){
                this->widgetListSearch->addItem(QString::fromStdString(it->getFormat()+ot->getFormat()));
            }
        }
    }else{ // grab par tag
        // ligne de forceur
        for(auto &it: *this->cata->getTagList()->findTag(tmp)->getInteraction()){
            this->widgetListSearch->addItem(QString::fromStdString(it->getContact()->getFormat()+it->getFormat()));
        }
    }
}

void WidgetSearch::deleteTag(){
    std::string tmp = this->widgetCombo->currentText().toStdString();
    if(tmp == "") return;
    this->cata->getTagList()->eraseTag(tmp);
    this->reloadSelf();
}

void WidgetSearch::printInter(QListWidgetItem* ptr){
     int index = this->widgetListSearch->row(ptr);
     std::string tmp = this->widgetCombo->currentText().toStdString();
     if(tmp=="") return;
     this->widgetListSearch->clear();
     if(tmp == DEFAULT_MESSAGE){
         for(auto &it: *this->cata->getContactLst()){
             for(auto &ot: *it->getInteractionLst()){
                 if(index==0){
                      emit sigInte(ot);
                      return;
                 }
                 index--;
             }
         }
     }else{ // grab par tag
         // ligne de forceur
         for(auto &it: *this->cata->getTagList()->findTag(tmp)->getInteraction()){
             if(index==0){
                 emit sigInte(it);
                 return;
             }
             index--;
         }
     }

}

void WidgetSearch::rechAvance(QString &s){
    for(int i=0; i<this->widgetListSearch->count();i++){
        if(this->widgetListSearch->item(i)->text().toLower().contains(s.toLower())){
            this->widgetListSearch->item(i)->setHidden(false);
        }else{
            this->widgetListSearch->item(i)->setHidden(true);
        }
    }
}
