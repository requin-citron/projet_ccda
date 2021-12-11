#include "widgetsearch.hpp"

WidgetSearch::WidgetSearch(ContactCatalog *cata) : QWidget(), cata(cata) {
    // modification rapide du css pour reduire la taille
    widgetListSearch->setStyleSheet("QListWidget {font-size: 20px;}");
    // construire les composants avec les bon texte
    paintInterface();
    // construction de l'interface
    QGridLayout *l1 = new QGridLayout;
    l1->addWidget(widgetCombo,0,0,1,3);
    l1->addWidget(widgetSuprr,0,3);
    QVBoxLayout *l2 = new QVBoxLayout;
    l2->addLayout(l1);
    l2->addWidget(widgetListSearch);
    l2->addWidget(widgetBack);
    setLayout(l2);
    // pour quitter la recherche
    QObject::connect(widgetBack,SIGNAL(clicked()), this , SLOT(handlerBack()));
    // changement dans la list deroulante
    QObject::connect(widgetCombo,SIGNAL(currentTextChanged(const QString&)),this, SLOT(reloadOnChange(const QString&)));
    // suppresion d'un tag
    QObject::connect(widgetSuprr, SIGNAL(clicked()), this, SLOT(deleteTag()));
    // double clic sur une interaction
    QObject::connect(widgetListSearch, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(printInter(QListWidgetItem*)));
    // recharge la combo
    reloadSelf();
}

void WidgetSearch::paintInterface() {
    // redefinition de chaque composant avec du texte pour charger la traduction
    widgetBack->setText(tr("Retour"));
    widgetSuprr->setText(tr("Supprimer le tag"));
}

void WidgetSearch::handlerBack(){
    emit goBack();
}

void WidgetSearch::reloadSelf(){
    // recharge la combo
    widgetCombo->clear();
    widgetCombo->addItem(DEFAULT_MESSAGE);
    for(auto &it: *cata->getTagList()->getTagList()){
        widgetCombo->addItem(QString::fromStdString(it->getName()));
    }
    reloadOnChange(this->widgetCombo->currentText());
}

void WidgetSearch::reloadOnChange(const QString &text){
    // selectionne toutes les interactions
    std::string tmp = text.toStdString();
    if(text.toStdString()=="") return;
    widgetListSearch->clear();
    if(tmp == DEFAULT_MESSAGE){
        for(auto &it: *cata->getContactLst()){
            for(auto &ot: *it->getInteractionLst()){
                widgetListSearch->addItem(QString::fromStdString(it->getFormat()+ot->getFormat()));
            }
        }
    }else{ // grab par tag
        for(auto &it: *cata->getTagList()->findTag(tmp)->getInteraction()){
            widgetListSearch->addItem(QString::fromStdString(it->getContact()->getFormat()+it->getFormat()));
        }
    }
}

void WidgetSearch::deleteTag(){
    std::string tmp = widgetCombo->currentText().toStdString();
    if(tmp == "") return;
    cata->getTagList()->eraseTag(tmp);
    reloadSelf();
}

Interaction *WidgetSearch::searchInte(QListWidgetItem* ptr){
    int index = widgetListSearch->row(ptr);
    std::string tmp = widgetCombo->currentText().toStdString();
    if(tmp=="") return NULL;
    widgetListSearch->clear();
    if(tmp == DEFAULT_MESSAGE){
        for(auto &it: *cata->getContactLst()){
            for(auto &ot: *it->getInteractionLst()){
                if(index==0){
                     return ot;
                }
                index--;
            }
        }
    }else{ // grab par tag
        for(auto &it: *cata->getTagList()->findTag(tmp)->getInteraction()){
            if(index==0){
                return it;
            }
            index--;
        }
    }
    return NULL;
}

void WidgetSearch::printInter(QListWidgetItem* ptr){
    Interaction *tmp = this->searchInte(ptr);
    if(tmp == NULL) return;
     emit sigInte(tmp);

}

void WidgetSearch::rechAvance(QString &s){
    // Lors de l'edition da la bar de recherche de la toolbar c'est cette focntion qui affine la liste
    for(int i=0; i<widgetListSearch->count();i++){
        if(widgetListSearch->item(i)->text().toLower().contains(s.toLower())){
            widgetListSearch->item(i)->setHidden(false);
        }else{
            widgetListSearch->item(i)->setHidden(true);
        }
    }
}

Interaction* WidgetSearch::getSelectItem(){
    return this->searchInte(this->widgetListSearch->currentItem());
}

QString WidgetSearch::getTag(){
    return this->widgetCombo->currentText();
}
