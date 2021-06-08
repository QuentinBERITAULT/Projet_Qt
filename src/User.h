#ifndef CPP_QT_TPMINIPROJET_USER_H
#define CPP_QT_TPMINIPROJET_USER_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include "MyScene.h"

class User : public QMainWindow{
    Q_OBJECT
private:
    QPushButton* button;

    QLabel* label;

    QFile* file;

    MyScene* verification_scene;

public:
    // Constructeur
    User();

    QLineEdit* text;

public slots:
    // Methodes
    void write();

    void verif(MyScene* scene);
};


#endif //CPP_QT_TPMINIPROJET_USER_H