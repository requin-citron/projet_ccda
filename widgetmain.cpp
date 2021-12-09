#include "widgetmain.hpp"

WidgetMain::WidgetMain(ContactCatalog *cata) : QWidget(), cata(cata) {
    widgetListContact->setStyleSheet("QListWidget {border : 2px solid black;background : lightgreen; font-size: 50px;}"
                                     "QListWidget QScrollBar {background : lightblue;}"
                                     "QListView::item:selected {border : 2px solid black;background : green;}");
    for (Contact* c: *cata->getContactLst())
        newContact(c);
    QPushButton *widgetAddContact = new QPushButton("Ajouter un Contact",this);
    QVBoxLayout *l1 = new QVBoxLayout;
    l1->addWidget(widgetListContact);
    l1->addWidget(widgetAddContact);
    setLayout(l1);

    QObject::connect(widgetAddContact, SIGNAL(clicked()),this, SLOT(createContact()));
    QObject::connect(widgetListContact, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(printContact(QListWidgetItem*)));
}

size_t WidgetMain::getIndexContact(Contact *c) {
    size_t t=0;
    for (Contact *tmp: *cata->getContactLst())
        if (tmp==c)
            break;
        else t++;
    return t;
}

Contact* WidgetMain::getContact(int index) {
    for (Contact *tmp: *cata->getContactLst())
        if (index--==0)
            return tmp;
    return nullptr;
}

void WidgetMain::newContact(Contact* c) {
    QListWidgetItem *tmp = new QListWidgetItem(QString::fromStdString(c->getFirstName()+" "+c->getLastName()+" ("+std::to_string(c->getId())+")"));
    tmp->setTextAlignment(Qt::AlignHCenter);
    widgetListContact->addItem(tmp);
}

void WidgetMain::removeContact(Contact *c) {
    widgetListContact->takeItem(static_cast<int>(getIndexContact(c)));
    cata->eraseContact(c);
}

void WidgetMain::createContact() {
    Contact* c = cata->addContact("Jean","Dupont","superEntreprise","jeanDupont@example.com","06...","picture.png");
    newContact(c);
    emit printContact(c);
}

void WidgetMain::refreshListWidget(Contact* c) {
    widgetListContact->item(static_cast<int>(getIndexContact(c)))->setText(QString::fromStdString(c->getFirstName()+" "+c->getLastName()+" ("+std::to_string(c->getId())+")"));
}

void WidgetMain::printContact(QListWidgetItem* i) {
    Contact *c = getContact(widgetListContact->row(i));
    if (c!=nullptr)
        emit printContact(c);
}
