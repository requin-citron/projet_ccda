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
    size_t getIndexContact(Contact* c);
    Contact* getContact(int index);
    void newContact(Contact* c);
private slots:
    void createContact();
    void printContact(QListWidgetItem* i);
signals:
    void printContact(Contact* c);
};

#endif // WIDGETMAIN_HPP
