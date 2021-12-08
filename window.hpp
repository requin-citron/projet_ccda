#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QtWidgets>
#include <iostream>
#include "contactCatalog.hpp"
#include "contact.hpp"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
public slots:
    void stackSwitch();
    void printContact(QListWidgetItem* c);
private:
    QWidget* mainwin();
    QWidget* contactwin();
    void printContact(QString photo, QString first, QString last, QString ent, QString mail, QString phone, std::list<Interaction*>* li);
    void printContact(Contact* c);
    QStackedLayout *stackedLay;
    ContactCatalog cata;
    QListWidget *widgetListContact = new QListWidget();
    std::map<QListWidgetItem*,Contact*> linkContact;

    QLabel *widgetPhoto = new QLabel("pathPicture");
    QLineEdit *widgetFirstName = new QLineEdit();
    QLineEdit *widgetLastName = new QLineEdit();
    QLineEdit *widgetEntreprise = new QLineEdit();
    QLineEdit *widgetMail = new QLineEdit();
    QLineEdit *widgetPhone = new QLineEdit();
    QListWidget *widgetListInteraction = new QListWidget();
};

#endif // WINDOW_HPP
