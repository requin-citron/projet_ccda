#include "window.hpp"
//addContact->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
Window::Window() : QMainWindow() {
    setWindowTitle("Gestionnaire de contact");
    setMinimumSize(800,800);

    QWidget *w = new QWidget();
    stackedLay = new QStackedLayout;
    stackedLay->addWidget(mainwin());
    stackedLay->addWidget(contactwin());
    w->setLayout(stackedLay);
    setCentralWidget(w);
}

QWidget* Window::mainwin() {
    QWidget *w = new QWidget();
    QListWidget *qlw = new QListWidget();
    qlw->setStyleSheet("QListWidget {border : 2px solid black;background : lightgreen; font-size: 50px;}"
                       "QListWidget QScrollBar {background : lightblue;}"
                       "QListView::item:selected {border : 2px solid black;background : green;}");
    for (int t=0; t<50; t++) {
        QListWidgetItem *tmp = new QListWidgetItem("item "+QString::number(t));
        tmp->setTextAlignment(Qt::AlignHCenter);
        //tmp->setSizeHint(QSize(0,200));
        linkContact[tmp] = "merde "+QString::number(t);
        qlw->addItem(tmp);
    }
    QPushButton *addContact = new QPushButton("Ajouter un Contact",this);
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(qlw);
    lay->addWidget(addContact);
    w->setLayout(lay);

    QObject::connect(qlw, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(printContact(QListWidgetItem*)));
    QObject::connect(addContact, SIGNAL(clicked()),this, SLOT(stackSwitch()));

    return w;
}

QWidget* Window::contactwin() {
    QWidget *w = new QWidget();

    QLabel *photo = new QLabel("pathPicture");
    photo->setPixmap(QPixmap("../file/picture.png"));
    QLineEdit *firstName = new QLineEdit("Dupont");
    QLineEdit *lastName = new QLineEdit("Jean");
    QLineEdit *entreprise = new QLineEdit("Orange");
    QLineEdit *mail = new QLineEdit("jeanDupont@example.com");
    QLineEdit *phone = new QLineEdit("06...");
    QListWidget *list_interaction = new QListWidget();
    for (int t=0; t<50; t++)
        list_interaction->addItem("Interaction "+QString::number(t));
    QPushButton *save = new QPushButton("Enregistrer");
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(stackSwitch()));

    QFormLayout *l1 = new QFormLayout;
    l1->addRow("Prénom", firstName);
    l1->addRow("Nom", lastName);
    l1->addRow("Entreprise", entreprise);
    l1->addRow("Mail", mail);
    l1->addRow("Téléphone", phone);
    QVBoxLayout *l2 = new QVBoxLayout;
    l2->addWidget(photo);
    l2->addLayout(l1);
    QVBoxLayout *l3 = new QVBoxLayout;
    l3->addWidget(new QLabel("Interactions :"));
    l3->addWidget(list_interaction);
    QHBoxLayout *l4 = new QHBoxLayout;
    l4->addLayout(l2);
    l4->addLayout(l3);
    QVBoxLayout *l5 = new QVBoxLayout;
    l5->addLayout(l4);
    l5->addWidget(save);
    w->setLayout(l5);

    return w;
}

void Window::printContact(QListWidgetItem* c) {
    stackSwitch();
    std::cout << linkContact[c].toStdString() << std::endl;
}

void Window::stackSwitch() {
    if (stackedLay->currentIndex()==1)
        stackedLay->setCurrentIndex(0);
    else
        stackedLay->setCurrentIndex(1);
}
