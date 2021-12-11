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
    //! changer le text de l'item referant le contact
    void refreshListWidget(Contact* c);
    //! supprimer un contact
    void removeContact(Contact* c);
    //! si on demande une recherche rapide
    void rechAvance(QString s);
    //! renvois le contact selectionne
    Contact *getCurrentContact();
private:
    //! variable pour acceder a la list des contacts
    ContactCatalog *cata;
    //! les widgets
    QListWidget *widgetListContact = new QListWidget();
    QPushButton *widgetAddContact = new QPushButton();
    //! accesseurs pour la liste
    size_t getIndexContact(Contact* c);
    Contact* getContact(int index);
    //! ajout d'un contact
    void newContact(Contact* c);
private slots:
    //! gestion du contact
    void createContact();
    void printContact(QListWidgetItem* i);
signals:
    //! demander a Windeow d'afficher un contact
    void printContact(Contact* c);
};

#endif // WIDGETMAIN_HPP
