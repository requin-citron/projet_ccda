#ifndef WIDGETHIST_HPP
#define WIDGETHIST_HPP

#include <QtWidgets>
#include "histlocal.hpp"

class WidgetHist : public QWidget
{
public:
    WidgetHist();
    void configHist(HistLocal* h);
private:
    QListWidget *widgetListHist = new QListWidget();

};

#endif // WIDGETHIST_HPP
