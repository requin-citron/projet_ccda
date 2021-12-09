#include "window.hpp"

Window::Window() : QMainWindow() {
    setWindowTitle("Gestionnaire de contact");
    setMinimumSize(800,800);
    QMenu *menuImporter = menuBar()->addMenu("Importer");
        QAction *actionBdd = new QAction("BDD");
        menuImporter->addAction(actionBdd);
        QAction *actionPicture = new QAction("Photos de profils");
        menuImporter->addAction(actionPicture);
    QMenu *menuExporter = menuBar()->addMenu("Exporter");
        QAction *actionJson = new QAction("Json");
        menuExporter->addAction(actionJson);
        actionJson->setShortcut(QKeySequence("Ctrl+s"));
    QMenu *menuLangue = menuBar()->addMenu("Langue");
        QAction *actionFr = new QAction("Français");
        menuLangue->addAction(actionFr);
        actionFr->setCheckable(true);
        actionFr->setChecked(true);
        QAction *actionEn = new QAction("Anglais");
        menuLangue->addAction(actionEn);
        actionEn->setCheckable(true);
    QMenu *menuAutre = menuBar()->addMenu("Autres");
        QAction *actionQuitter = new QAction("Quitter");
        menuAutre->addAction(actionQuitter);
        actionQuitter->setShortcut(QKeySequence("Ctrl+q"));
    QToolBar *toolBarRech = addToolBar("Recherche");
        QLineEdit *widgetRech = new QLineEdit("rech...");
        toolBarRech->addWidget(widgetRech);
        toolBarRech->addSeparator();
        QPushButton *widgetHist = new QPushButton("Historique");
        toolBarRech->addWidget(widgetHist);
        toolBarRech->addSeparator();
    cata.loadDataBase();
    wm = new WidgetMain(&cata);
    wc = new WidgetContact();
    layStacked = new QStackedLayout;
    layStacked->addWidget(wm);
    layStacked->addWidget(wc);
    QWidget *container = new QWidget();
    container->setLayout(layStacked);
    setCentralWidget(container);
}

Window::~Window() {
    ;
}

/*QWidget* Window::mainwin() {
    QWidget *w = new QWidget();
        widgetListContact = new QListWidget();
            widgetListContact->setStyleSheet("QListWidget {border : 2px solid black;background : lightgreen; font-size: 50px;}"
                               "QListWidget QScrollBar {background : lightblue;}"
                               "QListView::item:selected {border : 2px solid black;background : green;}");
            for (Contact* c: *cata.getContactLst()) {
                QListWidgetItem *tmp = new QListWidgetItem(QString::fromStdString(c->getFirstName()+" "+c->getLastName()));
                tmp->setTextAlignment(Qt::AlignHCenter);
                linkContact[tmp] = c;
                widgetListContact->addItem(tmp);
            }
        QPushButton *addContact = new QPushButton("Ajouter un Contact",this);
        QPushButton *histori = new QPushButton("Historique");
        QGridLayout *gri = new QGridLayout;
        gri->addWidget(addContact,0,0,1,3);
        gri->addWidget(histori,0,3);
        QVBoxLayout *lay = new QVBoxLayout;
            lay->addWidget(widgetListContact);
            lay->addLayout(gri);
    w->setLayout(lay);

    QObject::connect(widgetListContact, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(printContact(QListWidgetItem*)));
    QObject::connect(addContact, SIGNAL(clicked()),this, SLOT(createContact()));

    return w;
}*/

/*QWidget* Window::contactwin() {
    QWidget *w = new QWidget();
        printContact();
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
    w->setLayout(l5);

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(saveContact()));
    QObject::connect(widgetPhoto, SIGNAL(clicked()), this, SLOT(choosePhoto()));

    return w;
}*/

/*
void Window::choosePhoto() {
    QString fichier = QFileDialog::getOpenFileName(this, "Choisie l'image", QString(), "Images (*.png *.jpg *.jpeg)");
    QPixmap pixmap(fichier);
    if (pixmap.isNull()) {
        widgetPhoto->setText("Choisir une photo");
        widgetPhoto->setIcon(QIcon());
    } else {
        currentContact->setPathPicture(fichier.toStdString());
        widgetPhoto->setText("");
        widgetPhoto->setIcon(QIcon(pixmap));
        widgetPhoto->setIconSize(pixmap.rect().size());
    }
}

void Window::printContact(QString photo, QString first, QString last, QString ent, QString mail, QString phone, std::list<Interaction*>* li) {
    QPixmap pixmap(photo);
    if (pixmap.isNull()) {
        widgetPhoto->setText("Choisir une photo");
        widgetPhoto->setIcon(QIcon());
    } else {
        widgetPhoto->setText("");
        widgetPhoto->setIcon(QIcon(pixmap));
        widgetPhoto->setIconSize(pixmap.rect().size());
    }
    widgetFirstName->setText(first);
    widgetLastName->setText(last);
    widgetEntreprise->setText(ent);
    widgetMail->setText(mail);
    widgetPhone->setText(phone);
    widgetListInteraction->clear();
    if (li!=nullptr)
        for (Interaction* i: *li)
            widgetListInteraction->addItem(QString::fromStdString("\tInter ("+std::to_string(i->getId())+")\n"+i->getContenu()));
}

void Window::printContact(Contact* c) {
    printContact(QString::fromStdString(c->getPathPicture()),
                 QString::fromStdString(c->getFirstName()),
                 QString::fromStdString(c->getLastName()),
                 QString::fromStdString(c->getEnterprise()),
                 QString::fromStdString(c->getMail()),
                 QString::fromStdString(c->getPhone()),c->getInteractionLst());
}

void Window::printContact(QListWidgetItem* c) {
    currentWidgetItem = c;
    currentContact = linkContact[c];
    printContact(linkContact[c]);
    stackedLay->setCurrentIndex(1);
}

void Window::createContact() {
    currentContact = cata.addContact("Dupont","Jean","ExampleEnterprise","jeanDupont@example.com","06...","../file/picture.png");
    currentWidgetItem = nullptr;
    printContact(currentContact);
    stackedLay->setCurrentIndex(1);
}

void Window::saveContact() {
    stackedLay->setCurrentIndex(0);
    currentContact->setFirstName(widgetFirstName->text().toStdString());
    currentContact->setLastName(widgetLastName->text().toStdString());
    currentContact->setEnterprise(widgetEntreprise->text().toStdString());
    currentContact->setMail(widgetMail->text().toStdString());
    currentContact->setPhone(widgetPhone->text().toStdString());
    if (currentWidgetItem==nullptr) {
        QListWidgetItem *tmp = new QListWidgetItem(QString::fromStdString(currentContact->getFirstName()+" "+currentContact->getLastName()));
        tmp->setTextAlignment(Qt::AlignHCenter);
        linkContact[tmp] = currentContact;
        widgetListContact->addItem(tmp);
    }
    else {
        currentWidgetItem->setText(QString::fromStdString(currentContact->getFirstName()+" "+currentContact->getLastName()));
    }
    currentContact = nullptr;
    currentWidgetItem=nullptr;
}

void Window::stackSwitch() {
    currentContact = cata.addContact("../file/picture.png","Dupont","Jean","ExampleEnterprise","jeanDupont@example.com","06...");
    printContact(currentContact);
    if (stackedLay->currentIndex()==1)
        stackedLay->setCurrentIndex(0);
    else
        stackedLay->setCurrentIndex(1);
}
*/
