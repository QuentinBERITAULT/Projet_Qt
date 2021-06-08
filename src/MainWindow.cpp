#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    this->mainScene = new MyScene;

    this->mainView = new QGraphicsView;
    this->mainView->setScene(mainScene);

    this->mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    // Enlève la scroll bar horizontale
    this->mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);      // Enlève la scroll bar verticale
    this->mainView->setFixedSize(400,800);

    this->setCentralWidget(mainView);
    this->setWindowTitle("Mini-projet Qt/C++ de Quentin");         // Titre de la fenêtre
    this->resize(400, 800);

    mainScene->setSceneRect(0,0,400,800);

    helpMenu = menuBar()->addMenu(tr("Règles"));
    QAction* actionRegles = new QAction(tr("But"), this);
    connect(actionRegles, SIGNAL(triggered()), this, SLOT(slot_ButRegles()));
    helpMenu->addAction(actionRegles);
    QAction* actionRegles2 = new QAction(tr("Bouttons"), this);
    connect(actionRegles2, SIGNAL(triggered()), this, SLOT(slot_BouttonRegles()));
    helpMenu->addAction(actionRegles2);

    helpMenu = menuBar()->addMenu(tr("Record"));
    QAction* record = new QAction(tr("Score"), this);
    connect(record, SIGNAL(triggered()), this, SLOT(slot_Record()));
    helpMenu->addAction(record);

    helpMenu = menuBar()->addMenu(tr("Pseudo"));
    QAction* pseudo = new QAction(tr("Entrez le pseudo"), this);
    connect(pseudo, SIGNAL(triggered()), this, SLOT(slot_pseudo()));
    helpMenu->addAction(pseudo);

}

MainWindow::~MainWindow(){

}

void MainWindow::slot_ButRegles() {
    // Explication du but du jeu
    QMessageBox msgBox;
    msgBox.setWindowTitle("But");
    msgBox.setText("Le but du Jeu: \n"
                   "Bouger Homer à gauche ou à droite pour qu'il évite de manger les donuts ! \n"
                   "Pourquoi ? Tout simplement parce qu'il est en surpoids ! \n"
                   "Bonne chance ! \n");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::slot_BouttonRegles(){
    // Explication des boutons
    QMessageBox msgBox;
    msgBox.setWindowTitle("Boutons");
    msgBox.setText("Les boutons: \n"
                   "- Espace => Pour commencer la session de jeu (Donc seulement la première fois) \n"
                   "- Flèche de Gauche => Aller à Gauche \n"
                   "- Flèche de Droite => Aller à Droite \n"
                   "- P => Mettre en pause / Mettre en play \n"
                   "- R => Permet de relancer le jeu sans fermer la fenêtre \n"
                   "J'espère que tout est clair ! ;) \n");
    msgBox.setModal(true); // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::slot_Record(){

    // on récupère ce qu'il y a écrit dans le fichier best.txt
    QFile meilleurscore("../ressources/best.txt");
    meilleurscore.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray x = meilleurscore.readLine();
    score = x.toInt();
    meilleurscore.close();

    // on récupère ce qu'il y a écrit dans le fichier bestuser.txt
    QFile bestuser("../ressources/bestuser.txt");
    bestuser.open(QIODevice::ReadOnly | QIODevice::Text);
    QString chaine = bestuser.readLine();
    bestuser.close();

    // on affiche le meilleur score avec son pseudo
    QMessageBox msgBox;
    msgBox.setWindowTitle("Meilleur score et son Pseudo");
    msgBox.setText(QStringLiteral("Voici le meilleur score : %1. Il est détenu par : %2").arg(score).arg(chaine));
    msgBox.setModal(false);                 // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
    msgBox.exec();
}

void MainWindow::slot_pseudo(){
    // Fenetre pour rentrer son pseudo
    auto enter_user = new User;
    enter_user->verif(this->mainScene);
    enter_user->show();
}