#include "widgetcontact.hpp"

WidgetContact::WidgetContact() : QWidget() {
    QFormLayout *l1 = new QFormLayout;
    l1->addRow("Prénom", widgetFirstName);
    l1->addRow("Nom", widgetLastName);
    l1->addRow("Entreprise", widgetEntreprise);
    l1->addRow("Mail", widgetMail);
    l1->addRow("Téléphone", widgetPhone);
    QPushButton *widgetNewInter = new QPushButton(tr("Ajouter une interaction"));
    QVBoxLayout *l2 = new QVBoxLayout;
    l2->addWidget(widgetPhoto);
    l2->addLayout(l1);
    l2->addWidget(widgetNewInter);
    QVBoxLayout *l3 = new QVBoxLayout;
    l3->addWidget(new QLabel("Interactions :"));
    l3->addWidget(widgetListInteraction);
    QHBoxLayout *l4 = new QHBoxLayout;
    l4->addLayout(l2);
    l4->addLayout(l3);
    QPushButton *widgetSave = new QPushButton(tr("Enregistrer"));
    QPushButton *widgetDel = new QPushButton(tr("Supprimer"));
    QGridLayout *l5 = new QGridLayout;
    l5->addWidget(widgetSave,0,0,1,3);
    l5->addWidget(widgetDel,0,3);
    QVBoxLayout *l6 = new QVBoxLayout;
    l6->addLayout(l4);
    l6->addLayout(l5);
    setLayout(l6);

    QObject::connect(widgetFirstName, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetLastName, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetEntreprise, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetMail, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetPhone, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetPhoto, SIGNAL(clicked()), this, SLOT(choosePhoto()));
    QObject::connect(widgetListInteraction, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(printInter(QListWidgetItem*)));
    QObject::connect(widgetNewInter, SIGNAL(clicked()),this, SLOT(createInter()));
    QObject::connect(widgetSave, SIGNAL(clicked()), this, SLOT(quitter()));
    QObject::connect(widgetDel, SIGNAL(clicked()), this, SLOT(deleteContact()));
}

void WidgetContact::paintInterface() {

}

Contact* WidgetContact::getContact() {return currentContact;}

void WidgetContact::configContact(Contact* c) {
    currentContact = c;
    QPixmap pixmap(QString::fromStdString(url+c->getPathPicture()));
    if (pixmap.isNull()) {
        widgetPhoto->setText(tr("Choisir une photo"));
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
    refreshInteraction();
}

void WidgetContact::refreshInteraction() {
    widgetListInteraction->clear();
    for (Interaction* i: *currentContact->getInteractionLst()) {
        QString tmp = QString::fromStdString(i->getContenu());
        tmp.replace(tmp.indexOf("\n"),1,'-');
        if (tmp.size()>=30)
            tmp = tmp.left(30)+"...";
        tmp = QString::fromStdString("\tInter ("+std::to_string(i->getId())+")\n")+tmp;
        widgetListInteraction->addItem(tmp);
    }
}

void WidgetContact::quitter() {emit refreshContact(currentContact);}

void WidgetContact::changeContact() {
    if (widgetFirstName->text().toStdString()!=currentContact->getFirstName())
        currentContact->setFirstName(widgetFirstName->text().toStdString());
    if (widgetLastName->text().toStdString()!=currentContact->getLastName())
        currentContact->setLastName(widgetLastName->text().toStdString());
    if (widgetEntreprise->text().toStdString()!=currentContact->getEnterprise())
        currentContact->setEnterprise(widgetEntreprise->text().toStdString());
    if (widgetMail->text().toStdString()!=currentContact->getMail())
        currentContact->setMail(widgetMail->text().toStdString());
    if (widgetPhone->text().toStdString()!=currentContact->getPhone())
        currentContact->setPhone(widgetPhone->text().toStdString());
}

void WidgetContact::deleteContact() {emit removeContact(currentContact);}

void WidgetContact::choosePhoto() {
    QString fichier = QFileDialog::getOpenFileName(this, tr("Choisie l'image"), QString::fromStdString(url), "Images (*.png *.jpg *.jpeg)");
    QPixmap pixmap(fichier);
    if (pixmap.isNull()) {
        widgetPhoto->setText(tr("Choisir une photo"));
        widgetPhoto->setIcon(QIcon());
    } else {
        int ind = fichier.lastIndexOf('/')+1;
        QString urlTmp = fichier.left(ind);
        QString nameFile = fichier.right(fichier.size()-ind);
        if (urlTmp.toStdString()==url)
            currentContact->setPathPicture(nameFile.toStdString());
        else {
            QFile::copy(fichier, QString::fromStdString(url+"backup_")+nameFile);
            currentContact->setPathPicture("backup_"+nameFile.toStdString());
        }
        widgetPhoto->setText("");
        widgetPhoto->setIcon(QIcon(pixmap));
        widgetPhoto->setIconSize(pixmap.rect().size());
    }
}

void WidgetContact::changePathPicture() {
    url = QFileDialog::getExistingDirectory(this, tr("Renseignez la position du fichier d'image"), QString::fromStdString(url)).toStdString()+"/";
}

Interaction* WidgetContact::getInteraction(int index) {
    for (Interaction *tmp: *currentContact->getInteractionLst())
        if (index--==0)
            return tmp;
    return nullptr;
}

void WidgetContact::printInter(QListWidgetItem* i) {
    Interaction* tmp = getInteraction(widgetListInteraction->row(i));
    if (tmp!=nullptr)
        emit printInter(tmp);
}

void WidgetContact::createInter() {
    emit printInter(currentContact->addInteraction("interaction...","tag..."));
}
