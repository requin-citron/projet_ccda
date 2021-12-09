#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QtWidgets>
#include <iostream>
#include "contactCatalog.hpp"
#include "contact.hpp"
#include "widgetmain.hpp"
#include "widgetcontact.hpp"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
    ~Window();
private:
    WidgetMain *wm;
    WidgetContact *wc;
    ContactCatalog cata;
    QStackedLayout *layStacked;
private slots:
    std::string initPathBdd();
    void editContact(Contact* c);
    void changeFocusMain(Contact* c);
    void removeContact(Contact* c);
    /*public slots:
        void stackSwitch();
        void printContact(QListWidgetItem* c);
        void createContact();
        void saveContact();
        void choosePhoto();*/
    //QWidget* mainwin();
    //QWidget* contactwin();
    /*void printContact(QString photo = "../file/picture.png",
                              QString first = "Dupont", QString last = "Jean", QString ent = "ExampleEnterprise",
                              QString mail = "jeanDupont@example.com", QString phone = "06...",
                              std::list<Interaction*>* li = nullptr);
    void printContact(Contact* c);*/
    /*Contact *currentContact = nullptr;
    QListWidgetItem *currentWidgetItem = nullptr;*/

    /*ContactCatalog cata;
    QListWidget *widgetListContact = new QListWidget();
    std::map<QListWidgetItem*,Contact*> linkContact;

    QPushButton *widgetPhoto = new QPushButton();
    QLineEdit *widgetFirstName = new QLineEdit();
    QLineEdit *widgetLastName = new QLineEdit();
    QLineEdit *widgetEntreprise = new QLineEdit();
    QLineEdit *widgetMail = new QLineEdit();
    QLineEdit *widgetPhone = new QLineEdit();
    QListWidget *widgetListInteraction = new QListWidget();*/
};

#endif // WINDOW_HPP
