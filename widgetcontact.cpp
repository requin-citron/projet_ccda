#include "widgetcontact.hpp"

WidgetContact::WidgetContact(std::string url) : QWidget() {
    this->url = url;
    this->widgetListInteraction->setStyleSheet("QListWidget {font-size: 20px;}");
    paintInterface();
    QFormLayout *l1 = new QFormLayout;
    l1->addRow(writePre, widgetFirstName);
    l1->addRow(writeNom, widgetLastName);
    l1->addRow(writeEnt, widgetEntreprise);
    l1->addRow(writeMail, widgetMail);
    l1->addRow(writeTel, widgetPhone);
    QVBoxLayout *l2 = new QVBoxLayout;
    l2->addWidget(widgetPhoto);
    l2->addLayout(l1);
    l2->addWidget(widgetNewInter);
    QVBoxLayout *l3 = new QVBoxLayout;
    l3->addWidget(new QLabel("Interaction :"));
    l3->addWidget(widgetListInteraction);
    QHBoxLayout *l4 = new QHBoxLayout;
    l4->addLayout(l2);
    l4->addLayout(l3);
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
    // redefinition de chaque composant avec du texte pour charger la traduction
    writePre->setText(tr("Prénom"));
    writeNom->setText(tr("Nom"));
    writeEnt->setText(tr("Entreprise"));
    writeMail->setText(tr("Mail"));
    writeTel->setText(tr("Téléphone"));
    widgetNewInter->setText(tr("Ajouter une interaction"));
    widgetSave->setText(tr("Enregistrer"));
    widgetDel->setText(tr("Supprimer"));
    if (currentContact!=nullptr)
        displayPhoto(QString::fromStdString(url+"/"+currentContact->getPathPicture()));
}

Contact* WidgetContact::getContact() {return currentContact;}

void WidgetContact::configContact(Contact* c) {
    currentContact = c;
    widgetFirstName->setText(QString::fromStdString(c->getFirstName()));
    widgetLastName->setText(QString::fromStdString(c->getLastName()));
    widgetEntreprise->setText(QString::fromStdString(c->getEnterprise()));
    widgetMail->setText(QString::fromStdString(c->getMail()));
    widgetPhone->setText(QString::fromStdString(c->getPhone()));
    displayPhoto(QString::fromStdString(url+"/"+c->getPathPicture()));
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

void WidgetContact::rechAvance(QString s) {
    for (int t=0; t<widgetListInteraction->count(); t++)
        if (widgetListInteraction->item(t)->text().toLower().contains(s.toLower()))
            widgetListInteraction->item(t)->setHidden(false);
        else
            widgetListInteraction->item(t)->setHidden(true);
}

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
    displayPhoto(fichier);
}

void WidgetContact::displayPhoto(QString path){
    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        widgetPhoto->setText(tr("Choisir une photo"));
        widgetPhoto->setIcon(QIcon());
    } else {
        int ind = path.lastIndexOf('/')+1;
        QString urlTmp = path.left(ind);
        QString nameFile = path.right(path.size()-ind);
        if (urlTmp.toStdString()==(url+"/"))
            currentContact->setPathPicture(nameFile.toStdString());
        else {
            QFile::copy(path, QString::fromStdString(url+"/backup_")+nameFile);
            currentContact->setPathPicture("backup_"+nameFile.toStdString());
        }
        widgetPhoto->setText("");
        widgetPhoto->setIcon(QIcon(pixmap));
        widgetPhoto->setIconSize(pixmap.rect().size());
    }
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
