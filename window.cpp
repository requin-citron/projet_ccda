#include "window.hpp"

Window::Window() : QMainWindow() {
    cata.loadDataBase(initPathBdd());

    setMinimumSize(800,800);
    actionLangues[0] = new QAction();
    actionLangues[1] = new QAction();
    actionLangues[0]->setCheckable(true);
    actionLangues[0]->setChecked(true);
    actionLangues[0]->setEnabled(false);
    actionLangues[1]->setCheckable(true);
    actionJson->setShortcut(QKeySequence("Ctrl+s"));
    actionQuitter->setShortcut(QKeySequence("Ctrl+q"));
    QToolBar *toolBarRech = addToolBar("Recherche");
    toolBarRech->addWidget(widgetRech);
    toolBarRech->addSeparator();
    toolBarRech->addWidget(widgetHist);
    toolBarRech->addSeparator();
    paintInterface();

    wm = new WidgetMain(&cata);
    wc = new WidgetContact();
    wh = new WidgetHist();
    wi = new WidgetInter();
    layStacked = new QStackedLayout;
    layStacked->addWidget(wm);
    layStacked->addWidget(wc);
    layStacked->addWidget(wh);
    layStacked->addWidget(wi);
    QWidget *container = new QWidget();
    container->setLayout(layStacked);
    setCentralWidget(container);

    QObject::connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionPicture, SIGNAL(triggered()), wc, SLOT(changePathPicture()));
    QObject::connect(actionChangePathTrad, SIGNAL(triggered()), this, SLOT(changePathTranslate()));
    QObject::connect(actionJson, SIGNAL(triggered()), this, SLOT(saveJson()));
    QObject::connect(actionLangues[0], SIGNAL(triggered()), this, SLOT(changeLangue()));
    QObject::connect(actionLangues[1], SIGNAL(triggered()), this, SLOT(changeLangue()));
    QObject::connect(widgetRech, SIGNAL(textChanged(QString)), this, SLOT(rechAvance(QString)));
    QObject::connect(widgetHist, SIGNAL(clicked()), this, SLOT(printHist()));
    QObject::connect(wm, SIGNAL(printContact(Contact*)), this, SLOT(editContact(Contact*)));
    QObject::connect(wc, SIGNAL(refreshContact(Contact*)), this, SLOT(changeFocusMain(Contact*)));
    QObject::connect(wc, SIGNAL(removeContact(Contact*)), this, SLOT(removeContact(Contact*)));
    QObject::connect(wc, SIGNAL(printInter(Interaction*)), this, SLOT(editInter(Interaction*)));
    QObject::connect(wh, SIGNAL(quitterHist()), this, SLOT(quitterHist()));
    QObject::connect(wi, SIGNAL(refreshInteraction()), this, SLOT(changeFocusInteraction()));
    QObject::connect(wi, SIGNAL(deleteInteraction()), this, SLOT(deleteInteraction()));
}

void Window::paintInterface() {
    setWindowTitle(tr("Gestionnaire de contact"));
    menuBar()->clear();
    QMenu *menuImporter = menuBar()->addMenu(tr("Intégrer"));
        actionPicture->setText(tr("Dossier - photo de profil"));
        menuImporter->addAction(actionPicture);
        actionChangePathTrad->setText(tr("Fichier - module de traduction"));
        menuImporter->addAction(actionChangePathTrad);
    QMenu *menuExporter = menuBar()->addMenu(tr("Exporter"));
        actionJson->setText("Json");
        menuExporter->addAction(actionJson);
    QMenu *menuLangue = menuBar()->addMenu(tr("Langue"));
        actionLangues[0]->setText(tr("Français"));
        menuLangue->addAction(actionLangues[0]);
        actionLangues[1]->setText(tr("Anglais"));
        menuLangue->addAction(actionLangues[1]);
    QMenu *menuAutre = menuBar()->addMenu(tr("Autre"));
        actionQuitter->setText(tr("Quitter"));
        menuAutre->addAction(actionQuitter);
    widgetHist->setText(tr("Historique"));
}

Window::~Window() {
    delete actionLangues[0];
    delete actionLangues[1];
    delete[] actionLangues;
    //cata.saveDataBase();
}

void Window::giveApp(QApplication *a) {app=a;}

void Window::saveJson() {
    std::string text = cata.saveJson();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarder en Json"));
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << QString::fromStdString(text+"\n");
    }
}

void Window::rechAvance(QString s) {
    if (layStacked->currentWidget()==wm)
        wm->rechAvance(s);
}

void Window::changeLangue() {
    if (trans==nullptr) changePathTranslate();
    if (actionLangues[0]->isEnabled()) {
        actionLangues[0]->setEnabled(false);
        actionLangues[1]->setEnabled(true);
        actionLangues[1]->setChecked(false);
        app->removeTranslator(trans);
    } else {
        actionLangues[0]->setEnabled(true);
        actionLangues[1]->setEnabled(false);
        actionLangues[0]->setChecked(false);
        app->installTranslator(trans);
    }  
    paintInterface();
    wm->paintInterface();
    wc->paintInterface();
    wi->paintInterface();
    wh->paintInterface();
}

std::string Window::initPathBdd() {
   QString url = QFileDialog::getOpenFileName(this, tr("Renseignez la position de la BDD"));
   return url.toStdString();
}

void Window::changePathTranslate() {
    trans = new QTranslator();
    trans->load(QFileDialog::getOpenFileName(this, tr("Renseignez la position du fichier de traduction")));
}

void Window::editContact(Contact* c) {
    wc->configContact(c);
    layStacked->setCurrentWidget(wc);
}

void Window::editInter(Interaction* i) {
    wi->configInter(i);
    layStacked->setCurrentWidget(wi);
}

void Window::changeFocusMain(Contact* c) {
    wm->refreshListWidget(c);
    layStacked->setCurrentWidget(wm);
    rechAvance(widgetRech->text());
}

void Window::deleteInteraction() {
    wc->getContact()->eraseInteraction(wi->getInter());
    changeFocusInteraction();
}

void Window::changeFocusInteraction() {
    wc->refreshInteraction();
    this->layStacked->setCurrentWidget(wc);
}

void Window::removeContact(Contact* c) {
    wm->removeContact(c);
    layStacked->setCurrentWidget(wm);
    rechAvance(widgetRech->text());
}

void Window::printHist() {
    widgetHist->setEnabled(false);
    if (layStacked->currentWidget()==wm) {
        wh->configHist(cata.getHist());
        currentWidgetTmp = wm;
    }
    else if (layStacked->currentWidget()==wi) {
        wh->configHist(wi->getInter()->getHist());
        currentWidgetTmp = wi;
    }
    else {
        wh->configHist(wc->getContact()->getHist());
        currentWidgetTmp = wc;
    }
    layStacked->setCurrentWidget(wh);
}

void Window::quitterHist() {
    widgetHist->setEnabled(true);
    layStacked->setCurrentWidget(currentWidgetTmp);
    rechAvance(widgetRech->text());
    currentWidgetTmp = nullptr;
}

void Window::saveDataBase(){
    this->cata.saveDataBase();
}

