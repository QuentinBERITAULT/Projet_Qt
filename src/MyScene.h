#ifndef CPP_QT_TPMINIPROJET_MYSCENE_H
#define CPP_QT_TPMINIPROJET_MYSCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QFont>
#include <QTimer>
#include <ctime>
#include <cstdlib>
#include <QFile>
#include <QTextStream>
#include <cmath>
#include <QTextEdit>
#include <QColor>
#include <QMessageBox>


class MyScene : public QGraphicsScene {
Q_OBJECT

public:
    // Constructeur
    MyScene(QObject* parent = nullptr);

    // Destructeur
    virtual ~MyScene();

    bool champ_complete = false;

public slots:
    // Methodes
    void update();                              // MODIFIER LA VITESSE

private:
    QTimer* timer = new QTimer;

    QGraphicsPixmapItem* homer;
    QGraphicsPixmapItem* donut;
    QGraphicsPixmapItem* back;
    QGraphicsPixmapItem* accueil;
    QGraphicsPixmapItem* triste;
    QGraphicsPixmapItem* heureux;

    QGraphicsLineItem* ligne;

    QGraphicsTextItem* score;
    QGraphicsTextItem* meilleur;
    QGraphicsTextItem* Restart;
    QGraphicsTextItem* Pause;
    QGraphicsTextItem* page;
    QGraphicsTextItem* text_heureux;
    QGraphicsTextItem* perdu;
    QGraphicsTextItem* titre;

    QFile* Readfilebest;

    int count = 0;
    int best = 0;
    int vitesse = 0;

protected:
    void keyPressEvent(QKeyEvent* event);
};


#endif //CPP_QT_TPMINIPROJET_MYSCENE_H