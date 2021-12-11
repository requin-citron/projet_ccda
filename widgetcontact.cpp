#include "widgetcontact.hpp"

WidgetContact::WidgetContact(std::string url) : QWidget() {
    // enregistrement de l'url pour trouver les images
    this->url = url;
    // modification rapide du css pour reduire la taille
    this->widgetListInteraction->setStyleSheet("QListWidget {font-size: 20px;}");
    // construire les composants avec les bon texte
    paintInterface();
    // construction de l'interface
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
    // editer une information du contact
    QObject::connect(widgetFirstName, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetLastName, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetEntreprise, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetMail, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    QObject::connect(widgetPhone, SIGNAL(editingFinished()), this, SLOT(changeContact()));
    // editer la photo du contact
    QObject::connect(widgetPhoto, SIGNAL(clicked()), this, SLOT(choosePhoto()));
    // preparer le passage pour aller dans WidgetInter
    QObject::connect(widgetListInteraction, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(printInter(QListWidgetItem*)));
    // preparer le passage pour aller dans WidgetInter avec une nouvelle interaction
    QObject::connect(widgetNewInter, SIGNAL(clicked()),this, SLOT(createInter()));
    // retourner dans WidgetMain en sauvegardant
    QObject::connect(widgetSave, SIGNAL(clicked()), this, SLOT(quitter()));
    // retourner dans WidgetMain en supprimant le contact
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
    // configuration du contact lorsque WidgetMain demande d'afficher WidgetContact
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
    // recharger la liste des interactions, lors d'une edition ou lors du demarrage
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
    // Lors de l'edition da la bar de recherche de la toolbar c'est cette focntion qui affine la liste
    for (int t=0; t<widgetListInteraction->count(); t++)
        if (widgetListInteraction->item(t)->text().toLower().contains(s.toLower()))
            widgetListInteraction->item(t)->setHidden(false);
        else
            widgetListInteraction->item(t)->setHidden(true);
}

void WidgetContact::changeContact() {
    // edition du contact
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
    // modification de la photo
    QString fichier = QFileDialog::getOpenFileName(this, tr("Choisie l'image"), QString::fromStdString(url), "Images (*.png *.jpg *.jpeg)");
    displayPhoto(fichier);
}

void WidgetContact::displayPhoto(QString path){
    // affichage de la photo
    QPixmap pixmap(path);
    if (pixmap.isNull()) {
        // si on trouve pas de photo on affiche un texte
        widgetPhoto->setText(tr("Choisir une photo"));
        widgetPhoto->setIcon(QIcon());
    } else {
        // si on a bien trouve une image
        int ind = path.lastIndexOf('/')+1;
        // on recupaire le chemain
        QString urlTmp = path.left(ind);
        // on recupaire le nom
        QString nameFile = path.right(path.size()-ind);
        // on met a jours le nom du fichier dans contact
        if (urlTmp.toStdString()==(url+"/"))
            currentContact->setPathPicture(nameFile.toStdString());
        else {
            // si le chemin est different du chemin du fichier data on fais un backup sur le fichier data
            QFile::copy(path, QString::fromStdString(url+"/backup_")+nameFile);
            currentContact->setPathPicture("backup_"+nameFile.toStdString());
        }
        // et on met la photo sur le bouton
        widgetPhoto->setText("");
        widgetPhoto->setIcon(QIcon(pixmap));
        widgetPhoto->setIconSize(pixmap.rect().size());
    }
}

Interaction* WidgetContact::getInteraction(int index) {
    // fonction pour trouver list[index]
    for (Interaction *tmp: *currentContact->getInteractionLst())
        if (index--==0)
            return tmp;
    return nullptr;
}

void WidgetContact::printInter(QListWidgetItem* i) {
    // pour demander a Window d'afficher l'interaction
    Interaction* tmp = getInteraction(widgetListInteraction->row(i));
    if (tmp!=nullptr)
        emit printInter(tmp);
}

void WidgetContact::createInter() {
    // pour demander a Window d'afficher une nouvelle interaction
    emit printInter(currentContact->addInteraction("interaction...","tag..."));
}
