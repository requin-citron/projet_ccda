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
    //! pour recharger les composants avec du texte lors d'une changement de language
    void paintInterface();
    void refreshListWidget(Contact* c);
    void removeContact(Contact* c);
    void rechAvance(QString s);
private:
    ContactCatalog *cata;
    QListWidget *widgetListContact = new QListWidget();
    QPushButton *widgetAddContact = new QPushButton();
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
