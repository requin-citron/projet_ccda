#include "contactwindow.h"

ContactWindow::ContactWindow() : QDialog()
{
    //setWindowTitle("Gestionnaire de contact");
    //setMinimumSize(600,600);
    QListWidget *qlw = new QListWidget(this);
    for (int t=0; t<50; t++)
        qlw->addItem("Item "+QString::number(t));
    QPushButton *addContact = new QPushButton("choubidou un Contact",this);
    //addContact->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(qlw);
    lay->addWidget(addContact);
    setLayout(lay);
}
