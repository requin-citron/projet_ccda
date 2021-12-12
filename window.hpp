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
    QAction *actionDel = new QAction();
    QAction *actionInfo = new QAction();
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
    //! pour l'affinage rapide sur une interface
    void rechAvance(QString s);
    //! pour editer un contact
    void editContact(Contact* c);
    //! pour editer une interaction
    void editInter(Interaction* i);
    //! retourner dans le WidgetMain
    void changeFocusMain(Contact* c);
    //! retourner dans WidgetContact
    void changeFocusInteraction();
    //! aller dans WidgetSearch
    void changeFocusSearch();
    //! supprimer un contact
    void removeContact(Contact* c);
    //! sauvegarde en json
    void saveJson();
    //! changer la langue
    void changeLangue();
    //! aller dans WidgetHist
    void printHist();
    //! quitter WidgetHist
    void quitterHist();
    //! quitter WidgetSearch
    void quitterSearch();
    //! supprimer une interaction
    void deleteInteraction();
    //! supprime l'element courant
    void deleteSelected();
    //! affiche la boite de dialogue avec les info general
    void showInfo();
};

#endif // WINDOW_HPP
