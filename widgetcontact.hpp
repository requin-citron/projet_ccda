#ifndef WIDGETCONTACT_HPP
#define WIDGETCONTACT_HPP

#include <QtWidgets>
#include "contact.hpp"

class WidgetContact : public QWidget
{
    Q_OBJECT
public:
    WidgetContact();
    void configContact(Contact* c);
    Contact* getContact();
private:
    std::string url = "/home/thibaultdupre1999/CetC++/Qt/CDAA/projet_ccda/file/";
    Contact* currentContact = nullptr;
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
