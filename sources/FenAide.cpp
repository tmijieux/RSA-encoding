#include "FenAide.h"


FenAide::FenAide(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Aide du logiciel");
    
    aideText = new QTextEdit();
    aideText->setReadOnly(true);
    aideText->setFont(QFont("Comic"));
    aideText->setHtml("Pour utiliser ce logiciel il vous suffit de rentrer les clés public (e, n) et le message secret à transmetre pour crypter un message et de rentrer les clés privé (d, n) et le message crypté pour le décrypter !\n Si vous n'avez pas de clé, vous pouvez faire des tests en utilisant comme clé public (0, 0) et comme clé prive (0, 0). Ces clé seront automatiquement remplacé par des clés valides. \nBonne utilisation !"); 

    quit = new QPushButton("Fermer");

    vbox = new QVBoxLayout;
    vbox->addWidget(aideText);
    vbox->addWidget(quit);

    setFixedSize(350, 400);
    setLayout(vbox);

    connect(quit, SIGNAL(clicked()), this, SLOT(accept()));

}
