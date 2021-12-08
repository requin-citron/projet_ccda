#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QtWidgets>
#include "contactwindow.h"
#include <iostream>

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();
public slots:
    void switchStack();
private:
    QWidget* mainwin();
    QWidget* contactwin();

    QStackedLayout *stackedLay;
};

#endif // WINDOW_HPP
