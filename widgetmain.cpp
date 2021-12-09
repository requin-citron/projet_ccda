#include "widgetmain.hpp"

WidgetMain::WidgetMain(ContactCatalog *cata) : QWidget(), cata(cata) {
    widgetListContact->setStyleSheet("QListWidget {border : 2px solid black;background : lightgreen; font-size: 50px;}"
                                     "QListWidget QScrollBar {background : lightblue;}"
                                     "QListView::item:selected {border : 2px solid black;background : green;}");
    for (Contact* c: *cata->getContactLst()) {
        QListWidgetItem *tmp = new QListWidgetItem(QString::fromStdString(c->getFirstName()+" "+c->getLastName()));
        tmp->setTextAlignment(Qt::AlignHCenter);
        listItem.push_back(tmp);
        widgetListContact->addItem(tmp);
    }
    QPushButton *widgetAddContact = new QPushButton("Ajouter un Contact",this);
    QVBoxLayout *l1 = new QVBoxLayout;
    l1->addWidget(widgetListContact);
    l1->addWidget(widgetAddContact);
    setLayout(l1);
}
