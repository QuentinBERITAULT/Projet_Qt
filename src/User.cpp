#include "User.h"

User::User(){
    // Ce qui permet de créer la fenêtre pour écrire son pseudo ainsi que de l'écrire
    this->file = new QFile("../ressources/user.txt");
    this->setWindowTitle("Saisit du Pseudo");
    this->setMinimumSize(200,50);

    this->button = new QPushButton("Valider");
    this->label = new QLabel("Entrez votre pseudo :");
    this->text = new QLineEdit;

    QWidget* mainWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout();

    mainLayout->addWidget(label);
    mainLayout->addWidget(text);
    mainLayout->addWidget(button);

    mainWidget->setLayout(mainLayout);
    this->setCentralWidget(mainWidget);
    connect(button,SIGNAL(clicked()),this,SLOT(write()));
}

void User::write(){             // fonction qui permet d'écrire dans le fichier
    if(text->text() != "") {
        QString texte = this->text->text();
        file->open(QIODevice::WriteOnly | QIODevice::Text);
        file->resize(0);
        QTextStream stream(file);
        stream << texte;
        verification_scene->champ_complete = true;
        file->close();
        this->close();
    }
}

void User::verif(MyScene* scene){       // Pour vérifier si on a écrit un pseudo
    verification_scene = scene;
}