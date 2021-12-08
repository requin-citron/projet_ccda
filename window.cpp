#include "window.hpp"
//addContact->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
Window::Window() : QMainWindow() {
    setWindowTitle("Gestionnaire de contact");
    setMinimumSize(800,800);

    cata.loadDataBase();

    QWidget *w = new QWidget();
        stackedLay = new QStackedLayout;
            stackedLay->addWidget(mainwin());
            stackedLay->addWidget(contactwin());
    w->setLayout(stackedLay);
    setCentralWidget(w);
}

QWidget* Window::mainwin() {
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
        QVBoxLayout *lay = new QVBoxLayout;
            lay->addWidget(widgetListContact);
            lay->addWidget(addContact);
    w->setLayout(lay);

    QObject::connect(widgetListContact, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(printContact(QListWidgetItem*)));
    QObject::connect(addContact, SIGNAL(clicked()),this, SLOT(stackSwitch()));

    return w;
}

QWidget* Window::contactwin() {
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

    QObject::connect(save, SIGNAL(clicked()), this, SLOT(stackSwitch()));

    return w;
}

void Window::printContact(QString photo, QString first, QString last, QString ent, QString mail, QString phone, std::list<Interaction*>* li) {
    widgetPhoto->setPixmap(QPixmap(photo));
    widgetFirstName->setText(first);
    widgetLastName->setText(last);
    widgetEntreprise->setText(ent);
    widgetMail->setText(mail);
    widgetPhone->setText(phone);
    widgetListInteraction->clear();
    if (li!=nullptr)
        for (Interaction* i: *li)
            widgetListInteraction->addItem(QString::fromStdString(i->getContenu()));
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
    printContact(linkContact[c]);
    stackedLay->setCurrentIndex(1);
}

void Window::stackSwitch() {
    if (stackedLay->currentIndex()==1)
        stackedLay->setCurrentIndex(0);
    else
        stackedLay->setCurrentIndex(1);
}
