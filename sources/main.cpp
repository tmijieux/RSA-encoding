/*
Ce logiciel fut réaliser par Alexandre GAY avec la colaboration de Thomas MIJIEUX, Robin PHILIBERT et Armand COMPAROT
Les sources de ce logiciel sont libre et gratuite.
Toutes personnes ayant utilisé ce logiciel peut me donner son avis pour l'améliorer ou simplement dire son avis sur le forum du site http://protecinfo.redheberg.com . Cela me ferait le plus grand plaisir !
*/
#include <QTextCodec>
#include <QApplication>
#include "FenPrincipale.h"
 
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication app(argc, argv);
 
    FenPrincipale fenetre;
    fenetre.show();
 
    return app.exec();
}

