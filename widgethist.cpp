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
    // redefinition de chaque composant avec du texte pour charger la traduction
    widgetQuitter->setText(tr("Retour"));
}

void WidgetHist::rechAvance(QString s) {
    for (int t=0; t<widgetListHist->count(); t++)
        if (widgetListHist->item(t)->text().toLower().contains(s.toLower()))
            widgetListHist->item(t)->setHidden(false);
        else
            widgetListHist->item(t)->setHidden(true);
}

void WidgetHist::configHist(HistLocal* h) {
    widgetListHist->clear();
    for (auto cur: *h->getLst())
        widgetListHist->addItem(QString::fromStdString(cur->second.printAll()+"> "+cur->first));
}

void WidgetHist::quitter() {
    emit quitterHist();
}
