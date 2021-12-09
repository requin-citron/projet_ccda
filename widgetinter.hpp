#ifndef WIDGETINTER_HPP
#define WIDGETINTER_HPP

#include <QtWidgets>
#include "interaction.hpp"

class WidgetInter : public QWidget
{
    Q_OBJECT
public:
    WidgetInter();
    void configInter(Interaction* i);
private:
    QLabel *widgetNameContact = new QLabel("Dominique Marteau");
    QTextEdit *widgetContenu = new QTextEdit();
    QListWidget *widgetListTodo = new QListWidget();
    QLineEdit *widgetTags = new QLineEdit("merde, truc, bidule");
};

#endif // WIDGETINTER_HPP
