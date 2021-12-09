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
private slots:
    void saveContact();
    void deleteContact();
    void choosePhoto();
    void changePathPicture();
signals:
    void refreshContact(Contact *c);
    void removeContact(Contact *c);
};

#endif // WIDGETCONTACT_HPP
