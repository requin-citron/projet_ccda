#include "window.hpp"

Window::Window() : QWidget() {
    setWindowTitle("Application Trop FUN");
    setMinimumSize(800,600);
    QListWidget *qlw = new QListWidget(this);
    for (int t=0; t<100; t++)
        qlw->addItem("Item "+QString::number(t));
    qlw->addItem("dfkjidfhsdughs");
    QPushButton *addContact = new QPushButton("Add Contact",this);

    QVBoxLayout *qlv = new QVBoxLayout;
    QPushButton *b = new QPushButton("Bonjour",this);
    b->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    qlv->addWidget(b);
    b = new QPushButton("Choubidou",this);
    b->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    qlv->addWidget(b);
    b = new QPushButton("Patraque",this);
    b->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    qlv->addWidget(b);
    QHBoxLayout *qlh = new QHBoxLayout;
    QTextEdit *qte = new QTextEdit();
    qlh->addWidget(qte);
    qlh->addLayout(qlv);

    QGridLayout *lay = new QGridLayout;
    lay->addWidget(qlw, 0, 0, 5, 1);
    lay->addWidget(addContact, 5, 0);
    lay->addLayout(qlh, 0, 1, 6, 3);


    setLayout(lay);
}
