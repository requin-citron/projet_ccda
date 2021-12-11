#include "widgetmain.hpp"

WidgetMain::WidgetMain(ContactCatalog *cata) : QWidget(), cata(cata) {
    // ajout les contacts dans la list
    for (Contact* c: *cata->getContactLst())
        newContact(c);
    // construire les composants avec les bon texte
    paintInterface();
    // construction de l'interface
    QVBoxLayout *l1 = new QVBoxLayout;
    l1->addWidget(widgetListContact);
    l1->addWidget(widgetAddContact);
    setLayout(l1);

    // ajout d'un contact
    QObject::connect(widgetAddContact, SIGNAL(clicked()),this, SLOT(createContact()));
    // afficher un contact
    QObject::connect(widgetListContact, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(printContact(QListWidgetItem*)));
}

void WidgetMain::paintInterface() {
    // redefinition de chaque composant avec du texte pour charger la traduction
    widgetAddContact->setText(tr("Ajouter un Contact"));
}

void WidgetMain::rechAvance(QString s) {
    // Lors de l'edition da la bar de recherche de la toolbar c'est cette focntion qui affine la liste
    for (int t=0; t<widgetListContact->count(); t++)
        if (widgetListContact->item(t)->text().toLower().contains(s.toLower()))
            widgetListContact->item(t)->setHidden(false);
        else
            widgetListContact->item(t)->setHidden(true);
}

size_t WidgetMain::getIndexContact(Contact *c) {
    // trouver l'index du contact dans la liste
    size_t t=0;
    for (Contact *tmp: *cata->getContactLst())
        if (tmp==c)
            break;
        else t++;
    return t;
}

Contact* WidgetMain::getContact(int index) {
    // trouver un contact avec l'index
    for (Contact *tmp: *cata->getContactLst())
        if (index--==0)
            return tmp;
    return nullptr;
}

void WidgetMain::newContact(Contact* c) {
    // ajout du contact dans la list
    QListWidgetItem *tmp = new QListWidgetItem(QString::fromStdString(c->getFirstName()+" "+c->getLastName()+" ("+std::to_string(c->getId())+")"));
    tmp->setTextAlignment(Qt::AlignHCenter);
    widgetListContact->addItem(tmp);
}

void WidgetMain::removeContact(Contact *c) {
    // suppression d'un contact
    widgetListContact->takeItem(static_cast<int>(getIndexContact(c)));
    cata->eraseContact(c);
}

void WidgetMain::createContact() {
    // ajout d'un contact
    Contact* c = cata->addContact("Jean","Dupont","superEntreprise","jeanDupont@example.com","06...","picture.png");
    newContact(c);
    emit printContact(c);
}

void WidgetMain::refreshListWidget(Contact* c) {
    // changer le text de l'item referant le contact
    widgetListContact->item(static_cast<int>(getIndexContact(c)))->setText(QString::fromStdString(c->getFirstName()+" "+c->getLastName()+" ("+std::to_string(c->getId())+")"));
}

void WidgetMain::printContact(QListWidgetItem* i) {
    // demander l'affichage d'un contact
    Contact *c = getContact(widgetListContact->row(i));
    if (c!=nullptr)
        emit printContact(c);
}

Contact *WidgetMain::getCurrentContact(){
    if(this->widgetListContact->count() == 0) return NULL;
    return this->getContact(this->widgetListContact->row(this->widgetListContact->currentItem()));
}
