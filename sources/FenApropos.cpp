#include "FenApropos.h"


FenApropos::FenApropos(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Apropos du logiciel");
    
    aproposText = new QTextBrowser();
    aproposText->setReadOnly(true);
    aproposText->setFont(QFont("Comic"));
    aproposText->setHtml("Ce programme fut réalisé par Alexandre GAY avec le soutien d'Armand Comparot, de Thomas Mijieux et de Robin PHILIBERT. \n Les codes sources sont libre et gratuit, vous pouvez les retrouver sur le site à l'addresse <a href='http://protecinfo.redheberg.com'>protecinfo.redheberg</a> . \n Vous trouverez sur le site une page forum ou vous pourez donner votre avis sur le logiciel. \n Pour plus d'information n'hésitez pas à nous contacter sur le site ou par mail \n Merci d'utiliser notre logiciel."); 
    
    aproposText->setOpenExternalLinks ( true );

    quit = new QPushButton("Fermer");

    vbox = new QVBoxLayout;
    vbox->addWidget(aproposText);
    vbox->addWidget(quit);

    setFixedSize(350, 400);
    setLayout(vbox);

    connect(quit, SIGNAL(clicked()), this, SLOT(accept()));

}
