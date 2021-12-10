#ifndef WIDGETINTER_HPP
#define WIDGETINTER_HPP

#include <QtWidgets>
#include "interaction.hpp"

class WidgetInter : public QWidget
{
    Q_OBJECT
public:
    WidgetInter();
    Interaction* getInter();
    void configInter(Interaction* i);
private:
    Interaction* currentInter = nullptr;
    QLabel *widgetNameContact = new QLabel("Dominique Marteau");
    QTextEdit *widgetContenu = new QTextEdit();
    QListWidget *widgetListTodo = new QListWidget();
    QLineEdit *widgetTags = new QLineEdit("merde, truc, bidule");
    void refreshTodo();
private slots:
    void editText();
    void saveText();
signals:
    void refreshInteraction();
};

#endif // WIDGETINTER_HPP
