#include "widgetinter.hpp"

WidgetInter::WidgetInter() : QWidget() {
    QFormLayout *l1 = new QFormLayout;
    l1->addRow("Tags",widgetTags);
    QVBoxLayout *l2 = new QVBoxLayout;
    l2->addWidget(widgetContenu);
    l2->addLayout(l1);
    QLabel *widgetTitreTodo = new QLabel("Todos");
    widgetTitreTodo->setAlignment(Qt::AlignCenter);
    QVBoxLayout *l3 = new QVBoxLayout;
    l3->addWidget(widgetTitreTodo);
    l3->addWidget(widgetListTodo);
    QGridLayout *l4 = new QGridLayout;
    l4->addLayout(l2,0,0);
    l4->addLayout(l3,0,3,1,3);
    paintInterface();
    QGridLayout *l5 = new QGridLayout;
    l5->addWidget(widgetSave,0,0,1,3);
    l5->addWidget(widgetDel,0,3);
    widgetNameContact->setAlignment(Qt::AlignCenter);
    QVBoxLayout *l6 = new QVBoxLayout;
    l6->addWidget(widgetNameContact);
    l6->addLayout(l4);
    l6->addLayout(l5);
    setLayout(l6);

    QObject::connect(widgetContenu, SIGNAL(textChanged()), this, SLOT(editText()));
    QObject::connect(widgetTags, SIGNAL(editingFinished()), this, SLOT(editTag()));
    QObject::connect(widgetSave, SIGNAL(clicked()), this, SLOT(saveText()));
    QObject::connect(widgetDel, SIGNAL(clicked()), this, SLOT(delInter()));
}

void WidgetInter::paintInterface() {
    widgetSave->setText(tr("Enregistrer"));
    widgetDel->setText(tr("Supprimer"));
}

void WidgetInter::configInter(Interaction *i) {
    currentInter = i;
    textChange = false;
    widgetNameContact->setText(QString::fromStdString(i->getContact()->getFirstName()+" "+i->getContact()->getLastName()+" ("+std::to_string(i->getContact()->getId())+")"));
    widgetContenu->setText(QString::fromStdString(i->getContenu()));
    refreshTodo();
    QString tmp = "";
    for (Tag* t: *i->getTags())
        tmp+=QString::fromStdString(t->getName())+" ";
    widgetTags->setText(tmp.left(tmp.size()-1));
}

void WidgetInter::refreshTodo() {
    widgetListTodo->clear();
    for (auto t: *currentInter->getTodo())
        if (t->second!=nullptr)
            widgetListTodo->addItem(QString::fromStdString(t->second->print()+">\n"+t->first));
        else
            widgetListTodo->addItem(QString::fromStdString("->\n"+t->first));
}

Interaction* WidgetInter::getInter() {return currentInter;}

void WidgetInter::editText() {
    if (currentInter->getContenu()!=widgetContenu->toPlainText().toStdString()) {
        textChange = true;
        currentInter->setContenu(widgetContenu->toPlainText().toStdString(),false);
        refreshTodo();
    }
}

void WidgetInter::editTag() {
    std::stringstream ss (this->widgetTags->text().toStdString());
    std::string tmp;
    std::list<std::string> lst;
    while(getline(ss, tmp, ' '))
        if(tmp != "" && tmp != " ")
            lst.push_back(tmp);
    this->currentInter->mergeTag(&lst);
}

void WidgetInter::saveText(){
    if (textChange)
        currentInter->setContenu(this->widgetContenu->toPlainText().toStdString());
    emit refreshInteraction();
}

void WidgetInter::delInter() {
    emit deleteInteraction();
}
