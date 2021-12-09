#ifndef WIDGETCONTACT_HPP
#define WIDGETCONTACT_HPP

#include <QtWidgets>

class WidgetContact : public QWidget
{
public:
    WidgetContact();
private:
    QPushButton *widgetPhoto = new QPushButton();
    QLineEdit *widgetFirstName = new QLineEdit();
    QLineEdit *widgetLastName = new QLineEdit();
    QLineEdit *widgetEntreprise = new QLineEdit();
    QLineEdit *widgetMail = new QLineEdit();
    QLineEdit *widgetPhone = new QLineEdit();
    QListWidget *widgetListInteraction = new QListWidget();
};

#endif // WIDGETCONTACT_HPP
