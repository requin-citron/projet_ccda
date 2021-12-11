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
    void configHist(HistLocal* h);
    void rechAvance(QString s);
private:
    QListWidget *widgetListHist = new QListWidget();
    QPushButton *widgetQuitter = new QPushButton();
private slots:
    void quitter();
signals:
    void quitterHist();
};

#endif // WIDGETHIST_HPP
