#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <QtWidgets>
#include <iostream>
#include "contactCatalog.hpp"
#include "contact.hpp"
#include "widgetmain.hpp"
#include "widgetcontact.hpp"
#include "widgethist.hpp"
#include "widgetinter.hpp"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    Window(QApplication *a);
    ~Window();
    std::string url = "";
private:
    QApplication *app;
    QTranslator *trans = nullptr;
    QWidget *currentWidgetTmp = nullptr;
    QAction *actionQuitter = new QAction();
    QAction *actionJson = new QAction();
    WidgetMain *wm;
    WidgetContact *wc;
    WidgetHist *wh;
    WidgetInter *wi;
    ContactCatalog cata;
    QStackedLayout *layStacked;
    QAction** actionLangues = new QAction*[2];
    QPushButton *widgetHist = new QPushButton();
    QLineEdit *widgetRech = new QLineEdit();
    void paintInterface();
private slots:
    void rechAvance(QString s);
    void editContact(Contact* c);
    void editInter(Interaction* i);
    void changeFocusMain(Contact* c);
    void changeFocusInteraction();
    void removeContact(Contact* c);
    void saveJson();
    void changeLangue();
    void printHist();
    void quitterHist();
    void deleteInteraction();
};

#endif // WINDOW_HPP
