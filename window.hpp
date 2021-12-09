#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QtWidgets>
#include <iostream>
#include "contactCatalog.hpp"
#include "contact.hpp"
#include "widgetmain.hpp"
#include "widgetcontact.hpp"
#include "widgethist.hpp"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window();
    ~Window();
private:
    WidgetMain *wm;
    WidgetContact *wc;
    WidgetHist *wh;
    ContactCatalog cata;
    QStackedLayout *layStacked;
    QPushButton *widgetHist;
private slots:
    std::string initPathBdd();
    void editContact(Contact* c);
    void changeFocusMain(Contact* c);
    void removeContact(Contact* c);
    void saveJson();
    void printHist();
};

#endif // WINDOW_HPP
