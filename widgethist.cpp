#include "widgethist.hpp"

WidgetHist::WidgetHist() : QWidget() {
    QPushButton *widgetQuitter = new QPushButton("Quitter");
    QVBoxLayout *l1 = new QVBoxLayout;
    l1->addWidget(widgetListHist);
    l1->addWidget(widgetQuitter);
    setLayout(l1);
}

void WidgetHist::configHist(HistLocal* h) {

}
