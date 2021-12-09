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
    std::vector<QListWidgetItem*> listItem; // INUTIL JE CROISSSSS widgetListContact.item(0)
    size_t getIndexContact(Contact* c);
    size_t getIndexItem(QListWidgetItem* i);
    Contact* getContact(size_t t);
    void newContact(Contact* c);
private slots:
    void createContact();
    void printContact(QListWidgetItem* i);
signals:
    void printContact(Contact* c);
};

#endif // WIDGETMAIN_HPP
