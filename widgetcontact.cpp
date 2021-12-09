#include "widgetcontact.hpp"

WidgetContact::WidgetContact() : QWidget() {
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
    QPushButton *widgetSave = new QPushButton("Enregistrer");
    QPushButton *widgetDel = new QPushButton("Supprimer");
    QGridLayout *l5 = new QGridLayout;
    l5->addWidget(widgetSave,0,0,1,3);
    l5->addWidget(widgetDel,0,3);
    QVBoxLayout *l6 = new QVBoxLayout;
    l6->addLayout(l4);
    l6->addLayout(l5);
    setLayout(l6);

    QObject::connect(widgetSave, SIGNAL(clicked()), this, SLOT(saveContact()));
    QObject::connect(widgetDel, SIGNAL(clicked()), this, SLOT(deleteContact()));
}

void WidgetContact::configContact(Contact* c) {
    currentContact = c;
    QPixmap pixmap(QString::fromStdString(url+c->getPathPicture()));
    if (pixmap.isNull()) {
        widgetPhoto->setText("Choisir une photo");
        widgetPhoto->setIcon(QIcon());
    } else {
        widgetPhoto->setText("");
        widgetPhoto->setIcon(QIcon(pixmap));
        widgetPhoto->setIconSize(pixmap.rect().size());
    }
    widgetFirstName->setText(QString::fromStdString(c->getFirstName()));
    widgetLastName->setText(QString::fromStdString(c->getLastName()));
    widgetEntreprise->setText(QString::fromStdString(c->getEnterprise()));
    widgetMail->setText(QString::fromStdString(c->getMail()));
    widgetPhone->setText(QString::fromStdString(c->getPhone()));
    widgetListInteraction->clear();
    for (Interaction* i: *c->getInteractionLst()) {
        QString tmp = QString::fromStdString("\tInter ("+std::to_string(i->getId())+")\n"+i->getContenu());
        tmp.replace(tmp.indexOf("\n"),1,'-');
        if (tmp.size()>=20)
            tmp = tmp.left(20);
        widgetListInteraction->addItem(tmp);
    }
}

void WidgetContact::saveContact() {
    currentContact->setFirstName(widgetFirstName->text().toStdString());
    currentContact->setLastName(widgetLastName->text().toStdString());
    currentContact->setEnterprise(widgetEntreprise->text().toStdString());
    currentContact->setMail(widgetMail->text().toStdString());
    currentContact->setPhone(widgetPhone->text().toStdString());
    emit refreshContact(currentContact);
}

void WidgetContact::deleteContact() {

}
