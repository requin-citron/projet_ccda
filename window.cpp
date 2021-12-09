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
        QPushButton *widgetHist = new QPushButton("Historique");
        toolBarRech->addWidget(widgetHist);
        toolBarRech->addSeparator();
    wm = new WidgetMain(&cata);
    wc = new WidgetContact();
    layStacked = new QStackedLayout;
    layStacked->addWidget(wm);
    layStacked->addWidget(wc);
    QWidget *container = new QWidget();
    container->setLayout(layStacked);
    setCentralWidget(container);

    QObject::connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(actionPicture, SIGNAL(triggered()), wc, SLOT(changePathPicture()));
    QObject::connect(wm, SIGNAL(printContact(Contact*)), this, SLOT(editContact(Contact*)));
    QObject::connect(wc, SIGNAL(refreshContact(Contact*)), this, SLOT(changeFocusMain(Contact*)));
    QObject::connect(wc, SIGNAL(removeContact(Contact*)), this, SLOT(removeContact(Contact*)));
}

Window::~Window() {
    ;
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
