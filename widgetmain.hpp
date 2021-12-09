#ifndef WIDGETMAIN_HPP
#define WIDGETMAIN_HPP

#include <QtWidgets>
#include "contactCatalog.hpp"
#include <iostream>

class WidgetMain : public QWidget
{
    Q_OBJECT
public:
    WidgetMain(ContactCatalog *cata);
    void refreshListWidget(Contact* c);
    void removeContact(Contact* c);
private:
    ContactCatalog *cata;
    QListWidget *widgetListContact = new QListWidget();
    std::vector<QListWidgetItem*> listItem;
    size_t getIndexContact(Contact* c);
    void newContact(Contact* c);
private slots:
    void createContact();
signals:
    void wantNewContact(Contact* c);
};

#endif // WIDGETMAIN_HPP
