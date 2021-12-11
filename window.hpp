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
#include "widgetsearch.hpp"

class Window : public QMainWindow
{
    Q_OBJECT
public:
    //! on recupere un pointeur sur la QApplication pour appliquer le style et le module de traduction de maniere globale
    Window(QApplication *a);
    ~Window();
    //! l'url du fichier data
    std::string url = "";
private:
    //! le pointeur sur QApplication
    QApplication *app;
    //! le pointeur sur le module de traduction
    QTranslator *trans = nullptr;
    //! widget tampon pour stocker la page courante lorsqu'ont ce deplace sur l'historique ou la recherche avance
    QWidget *currentWidgetTmp = nullptr;
    //! widgets du menuBar (gerer globalement pour pouvoir appliquer la traduction)
    QAction *actionQuitter = new QAction();
    QAction *actionJson = new QAction();
    QAction *actionSearch = new QAction();
    QAction** actionLangues = new QAction*[2];
    //! widgets (gerer globalement pour pouvoir appliquer la traduction)
    QPushButton *widgetHist = new QPushButton();
    QLineEdit *widgetRech = new QLineEdit();
    //! toutes les pages qui composent notre interface
    WidgetMain *wm;
    WidgetContact *wc;
    WidgetHist *wh;
    WidgetInter *wi;
    WidgetSearch *ws;
    //! variable qui gere toutes la gestion
    ContactCatalog cata;
    //! le layout pour controller l'interface
    QStackedLayout *layStacked;
    //! pour recharger les composants avec du texte lors d'une changement de language
    void paintInterface();
private slots:
    void rechAvance(QString s);
    void editContact(Contact* c);
    void editInter(Interaction* i);
    void changeFocusMain(Contact* c);
    void changeFocusInteraction();
    void changeFocusSearch();
    void removeContact(Contact* c);
    void saveJson();
    void changeLangue();
    void printHist();
    void quitterHist();
    void quitterSearch();
    void deleteInteraction();
};

#endif // WINDOW_HPP
