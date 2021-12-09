#ifndef WIDGETHIST_HPP
#define WIDGETHIST_HPP

#include <QtWidgets>
#include "histlocal.hpp"

class WidgetHist : public QWidget
{
    Q_OBJECT
public:
    WidgetHist();
    void configHist(HistLocal* h);
private:
    QListWidget *widgetListHist = new QListWidget();
private slots:
    void quitter();
signals:
    void quitterHist();
};

#endif // WIDGETHIST_HPP
