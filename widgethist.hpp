#ifndef WIDGETHIST_HPP
#define WIDGETHIST_HPP

#include <QtWidgets>
#include "histlocal.hpp"

class WidgetHist : public QWidget
{
    Q_OBJECT
public:
    WidgetHist();
    //! pour recharger les composants avec du texte lors d'une changement de language
    void paintInterface();
    //! configurer l'historique
    void configHist(HistLocal* h);
    //! si on demande une recherche rapide
    void rechAvance(QString s);
private:
    // la liste d'historique
    QListWidget *widgetListHist = new QListWidget();
    //! le QPushButton (gerer en global pour pouvoir les traduires)
    QPushButton *widgetQuitter = new QPushButton();
private slots:
    void quitter();
signals:
    void quitterHist();
};

#endif // WIDGETHIST_HPP
