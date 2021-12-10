#include "widgethist.hpp"

WidgetHist::WidgetHist() : QWidget() {
    paintInterface();
    QVBoxLayout *l1 = new QVBoxLayout;
    l1->addWidget(widgetListHist);
    l1->addWidget(widgetQuitter);
    setLayout(l1);

    QObject::connect(widgetQuitter, SIGNAL(clicked()), this, SLOT(quitter()));
}

void WidgetHist::paintInterface() {
    widgetQuitter->setText(tr("Continuer"));
}

void WidgetHist::configHist(HistLocal* h) {
    widgetListHist->clear();
    for (auto cur: *h->getLst())
        widgetListHist->addItem(QString::fromStdString(cur->second.printAll()+"> "+cur->first));
}

void WidgetHist::quitter() {
    emit quitterHist();
}
