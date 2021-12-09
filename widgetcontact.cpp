#include "widgetcontact.hpp"

WidgetContact::WidgetContact() : QWidget() {
    QPushButton *save = new QPushButton("Enregistrer");
    QFormLayout *l1 = new QFormLayout;
    l1->addRow("Prénom", widgetFirstName);
    l1->addRow("Nom", widgetLastName);
    l1->addRow("Entreprise", widgetEntreprise);
    l1->addRow("Mail", widgetMail);
    l1->addRow("Téléphone", widgetPhone);
    QVBoxLayout *l2 = new QVBoxLayout;
    l2->addWidget(widgetPhoto);
    l2->addLayout(l1);
    QVBoxLayout *l3 = new QVBoxLayout;
    l3->addWidget(new QLabel("Interactions :"));
    l3->addWidget(widgetListInteraction);
    QHBoxLayout *l4 = new QHBoxLayout;
    l4->addLayout(l2);
    l4->addLayout(l3);
    QVBoxLayout *l5 = new QVBoxLayout;
    l5->addLayout(l4);
    l5->addWidget(save);
    setLayout(l5);
}
