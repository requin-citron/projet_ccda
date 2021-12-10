#ifndef WIDGETINTER_HPP
#define WIDGETINTER_HPP

#include <QtWidgets>
#include "interaction.hpp"

class WidgetInter : public QWidget
{
    Q_OBJECT
public:
    WidgetInter();
    void paintInterface();
    Interaction* getInter();
    void configInter(Interaction* i);
private:
    Interaction* currentInter = nullptr;
    bool textChange = false;
    QLabel *widgetNameContact = new QLabel();
    QTextEdit *widgetContenu = new QTextEdit();
    QListWidget *widgetListTodo = new QListWidget();
    QLineEdit *widgetTags = new QLineEdit();
    void refreshTodo();
private slots:
    void editText();
    void saveText();
    void delInter();
    void editTag();
signals:
    void refreshInteraction();
    void deleteInteraction();
};

#endif // WIDGETINTER_HPP
