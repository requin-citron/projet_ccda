#include "window.hpp"

Window::Window() : QMainWindow() {
    cata.loadDataBase(initPathBdd());
    setWindowTitle("Gestionnaire de contact");
    setMinimumSize(800,800);
    QMenu *menuImporter = menuBar()->addMenu("Linker");
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
        widgetHist = new QPushButton("Historique");
        toolBarRech->addWidget(widgetHist);
        toolBarRech->addSeparator();
    wm = new WidgetMain(&cata);
    wc = new WidgetContact();
    wh = new WidgetHist();
    layStacked = new QStackedLayout;
    layStacked->addWidget(wm);
    layStacked->addWidget(wc);
    layStacked->addWidget(wh);
    QWidget *container = new QWidget();
    container->setLayout(layStacked);
    setCentralWidget(container);

    QObject::connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionPicture, SIGNAL(triggered()), wc, SLOT(changePathPicture()));
    QObject::connect(actionJson, SIGNAL(triggered()), this, SLOT(saveJson()));
    QObject::connect(widgetHist, SIGNAL(clicked()), this, SLOT(printHist()));
    QObject::connect(wm, SIGNAL(printContact(Contact*)), this, SLOT(editContact(Contact*)));
    QObject::connect(wc, SIGNAL(refreshContact(Contact*)), this, SLOT(changeFocusMain(Contact*)));
    QObject::connect(wc, SIGNAL(removeContact(Contact*)), this, SLOT(removeContact(Contact*)));
    QObject::connect(wh, SIGNAL(quitterHist()), this, SLOT(quitterHist()));
}

Window::~Window() {
    ;
}

void Window::saveJson() {
    std::string text = cata.saveJson();
    QString fileName = QFileDialog::getSaveFileName(this, "Sauvegarder en Json");
    QFile file(fileName);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << QString::fromStdString(text+"\n");
    }
}

std::string Window::initPathBdd() {
   QString url = QFileDialog::getOpenFileName(this, "Renseignez la position de la BDD", "../");
   return url.toStdString();
}

void Window::editContact(Contact* c) {
    wc->configContact(c);
    layStacked->setCurrentWidget(wc);
}

void Window::changeFocusMain(Contact* c) {
    wm->refreshListWidget(c);
    layStacked->setCurrentWidget(wm);
}

void Window::removeContact(Contact* c) {
    wm->removeContact(c);
    layStacked->setCurrentWidget(wm);
}

void Window::printHist() {
    widgetHist->setEnabled(false);
    if (layStacked->currentWidget()==wm) {
        wh->configHist(cata.getHist());
        currentWidgetTmp = wm;
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
    currentWidgetTmp = nullptr;
}
