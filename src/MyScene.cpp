#include <QWidget>
#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>
#include "MyScene.h"
#include "MainWindow.h"

void MyScene::update() {
    int aleatoire = rand()%3;                                       // Tire un chiffre aléatoire entre 1, 2 et 3

    QPointF pos = donut->pos();                                     // récupération de la position de l'objet salade
    vitesse = log(0.05*count+1)+1;                               // Vitesse des donuts
    donut->setPos(pos.rx(), pos.ry()+vitesse);                  // incrémentation de la coordonnée y

    // Pour faire apparaître les donuts et augmenter le score
    if(donut->pos().ry()<=800){
        if(aleatoire == 0) {
            if (donut->collidesWithItem(ligne)) {
                donut->setPos(20, 0);
                count++;
                this->score->setPlainText(QStringLiteral("Score : %1").arg(count));
            }
        }
        if(aleatoire == 1) {
            if (donut->collidesWithItem(ligne)) {
                donut->setPos(160, 0);
                count++;
                this->score->setPlainText(QStringLiteral("Score : %1").arg(count));
            }
        }
        if(aleatoire == 2) {
            if (donut->collidesWithItem(ligne)) {
                donut->setPos(300, 0);
                count++;
                this->score->setPlainText(QStringLiteral("Score : %1").arg(count));
            }
        }
    }


    // Quand Game Over
    if(donut->collidesWithItem(homer)){
        timer->stop();
        Restart = new QGraphicsTextItem("Appuyez sur R pour recommencer !");
        Restart->setPos(110,220);
        this->addItem(Restart);

        this->removeItem(donut);
        this->removeItem(homer);
        this->addItem(triste);
        this->addItem(perdu);

        Readfilebest= new QFile("../ressources/best.txt");
        Readfilebest->open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray in = Readfilebest->readLine();
        best = in.toInt();
        Readfilebest->close();

        if(best < count){               // Quand on bat le meilleur score
            best = count;
            this->addItem(heureux);
            this->addItem(text_heureux);

            // On écrit le meilleur score dans le fichier best.txt
            QFile Writefilebest("../ressources/best.txt");
            Writefilebest.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream flux(&Writefilebest);                                // création objet flux QTextStream
            flux << best;                                           // envoie du texte dans le flux
            Writefilebest.close();
            this->meilleur->setPlainText(QStringLiteral("Meilleur score : %1").arg(best));

            // On lit le fichier user.txt et on écrit le pseudo dans le fichier bestuser.txt
            QFile bestuser("../ressources/user.txt");
            bestuser.open(QIODevice::ReadOnly | QIODevice::Text);
            QString chaine = bestuser.readLine();
            bestuser.close();

            QFile Writefilebestuser("../ressources/bestuser.txt");
            Writefilebestuser.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream flux_bestuser(&Writefilebestuser);
            flux_bestuser << chaine;
            Writefilebestuser.close();
        }
    }


}

void MyScene::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_P) {                 // appui sur la touche P du clavier
        if(timer->isActive()) {
            timer->stop();
            Pause = new QGraphicsTextItem("Partie mise en pause, appuyez sur P pour reprendre !");
            Pause->setPos(50,370);
            this->addItem(Pause);
        } else {
            timer->start();
            this->removeItem(Pause);
        }
    }

    if(event->key() == Qt::Key_Left){               // appui sur la fleche de gauche
        if(timer->isActive()){
            QPointF pos = homer->pos();
            if(pos.rx() - 135 >= 0) {
                homer->setPos(pos.rx() - 135, pos.ry());
            }
        }
    }

    if(event->key() == Qt::Key_Right){              // appui sur la fleche de droite
        if(timer->isActive()){
            QPointF pos = homer->pos();
            if(pos.rx() + 135 <= 400) {
                homer->setPos(pos.rx() + 135, pos.ry());
            }
        }
    }

    if(donut->collidesWithItem(homer)){
        int aleatoire = rand()%3;
        if(event->key() == Qt::Key_R){              // appui sur la touche R du clavier
            timer->start();
            donut->setPos( 20+aleatoire*140,0);
            homer->setPos(140,680);
            this->removeItem(Restart);
            this->addItem(homer);
            this->addItem(donut);
            this->removeItem(triste);
            this->removeItem(perdu);
            if (best == count) {
                this->removeItem(heureux);
                this->removeItem(text_heureux);
            }
            count = 0;
            this->score->setPlainText(QStringLiteral("Score : %1").arg(count));
        }
    }

    if(event->key() == Qt::Key_Space){      // appui sur la barre espace
        // Si il y a un pseudo de rentré
        if(champ_complete){
            timer->start(1);                //toutes les 1 millisecondes
            this->addItem(back);
            this->addItem(homer);
            this->addItem(donut);
            this->addItem(score);
            this->addItem(meilleur);
            this->addItem(ligne);
            this->removeItem(accueil);
            this->removeItem(page);
            this->removeItem(titre);
        }else {                                     // Si aucun pseudo est rentré
            QMessageBox msgBox;
            msgBox.setWindowTitle("ATTENTION !");
            msgBox.setText("N'oubliez pas de mettre un Pseudo !! "
                                "Car si vous dépassez le meilleur score, vous serez enregistré ! \n"
                                "En haut dans la barre, cliquez sur: \"Pseudo\" ");
            msgBox.setModal(true);                 // on souhaite que la fenetre soit modale i.e qu'on ne puisse plus cliquer ailleurs
            msgBox.exec();
        }
    }

}

MyScene::MyScene(QObject* parent) : QGraphicsScene(parent) {

    // Ecriture pour le titre
    QFont fontTitre;
    fontTitre.setPointSize(15);
    fontTitre.setUnderline(true);
    fontTitre.setBold(true);

    // Image de la page d'accueil
    QPixmap page_accueil("../ressources/accueil.png");
    this->accueil = new QGraphicsPixmapItem(page_accueil);
    accueil->setPos(0,0);
    this->addItem(accueil);

    // Image de fond pour le jeu
    QPixmap fond("../ressources/maison.png");
    this->back = new QGraphicsPixmapItem(fond);
    back->setPos(-130,0);

    // Image d'Homer
    QPixmap monimage("../ressources/homer.png");
    this->homer = new QGraphicsPixmapItem(monimage);
    homer->setPos(140,680);

    // Image de Donut
    int aleatoire = rand()%3;
    QPixmap monimage2("../ressources/donut.png");
    this->donut = new QGraphicsPixmapItem(monimage2);
    donut->setPos( 20+aleatoire*140,0);

    // Image de Homer triste quand on perd
    QPixmap fin("../ressources/triste.png");
    this->triste = new QGraphicsPixmapItem(fin);
    triste->setPos( 120,320);

    // Image de Homer heureux quand on bat le meilleur score
    QPixmap happy("../ressources/heureux.png");
    this->heureux = new QGraphicsPixmapItem(happy);
    heureux->setPos(200,73);

    // Afficher le score
    score = new QGraphicsTextItem(QStringLiteral("Score : %1").arg(count));
    score->setPos(5,15);

    // Afficher le meilleur score
    meilleur = new QGraphicsTextItem(QStringLiteral("Meilleur score : %1").arg(best));
    meilleur->setPos(5,5);

    // Texte de la première page
    page = new QGraphicsTextItem("Appuyez sur la barre espace \n"
                                      "          pour commencer !");
    page->setPos(130,640);
    this->addItem(page);

    // Texte quand on bat le meilleur score
    text_heureux = new QGraphicsTextItem("Wouhou ! Meilleur Score battu !!");
    text_heureux->setPos(170,50);

    // Texte quand on perd
    perdu = new QGraphicsTextItem("PERDU ! Homer a mangé un donut...");
    perdu->setPos(110,750);

    // Texte du titre
    titre = new QGraphicsTextItem("LE SURPOIDS DE HOMER");
    titre->setPos(2,5);
    titre->setFont(fontTitre);
    this->addItem(titre);

    // Ligne invisible, dès que le donut la touche, il réapparait
    ligne = new QGraphicsLineItem(0,800,400,800);


    Readfilebest = new QFile("../ressources/best.txt");
    Readfilebest->open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray in = Readfilebest->readLine();
    best = in.toInt();
    Readfilebest->close();
    this->meilleur->setPlainText(QStringLiteral("Meilleur score : %1").arg(best));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

MyScene::~MyScene() {

}