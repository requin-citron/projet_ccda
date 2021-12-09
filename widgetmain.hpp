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
private:
    ContactCatalog *cata;
    QListWidget *widgetListContact = new QListWidget();
    std::vector<QListWidgetItem*> listItem;
    void newContact(Contact* c);
private slots:
    void createContact();
signals:
    void wantNewContact(Contact* c);
};

#endif // WIDGETMAIN_HPP
