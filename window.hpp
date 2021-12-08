#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QtWidgets>
#include "contactwindow.h"
#include <iostream>

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
    std::map<QListWidgetItem*,QString> linkContact;
    QStackedLayout *stackedLay;
};

#endif // WINDOW_HPP
