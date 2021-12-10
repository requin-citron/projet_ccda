#ifndef WIDGETCONTACT_HPP
#define WIDGETCONTACT_HPP

#include <QtWidgets>
#include "contact.hpp"

class WidgetContact : public QWidget
{
    Q_OBJECT
public:
    WidgetContact();
    void paintInterface();
    void configContact(Contact* c);
    Contact* getContact();
    void refreshInteraction();
private:
    std::string url = "/home/thibaultdupre1999/CetC++/Qt/CDAA/projet_ccda/file/";
    Contact* currentContact = nullptr;
    QLabel *writePre = new QLabel();
    QLabel *writeNom = new QLabel();
    QLabel *writeEnt = new QLabel();
    QLabel *writeMail = new QLabel();
    QLabel *writeTel = new QLabel();
    QPushButton *widgetNewInter = new QPushButton();
    QPushButton *widgetSave = new QPushButton();
    QPushButton *widgetDel = new QPushButton();
    QPushButton *widgetPhoto = new QPushButton();
    QLineEdit *widgetFirstName = new QLineEdit();
    QLineEdit *widgetLastName = new QLineEdit();
    QLineEdit *widgetEntreprise = new QLineEdit();
    QLineEdit *widgetMail = new QLineEdit();
    QLineEdit *widgetPhone = new QLineEdit();
    QListWidget *widgetListInteraction = new QListWidget();
    Interaction* getInteraction(int index);
private slots:
    void quitter();
    void deleteContact();
    void choosePhoto();
    void changePathPicture();
    void changeContact();
    void printInter(QListWidgetItem* i);
    void createInter();
signals:
    void refreshContact(Contact *c);
    void removeContact(Contact *c);
    void printInter(Interaction *i);
};

#endif // WIDGETCONTACT_HPP
