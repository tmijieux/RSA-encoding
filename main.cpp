/*
Ce logiciel fut réaliser par Alexandre GAY avec la colaboration de Thomas MIJIEUX, Robin PHILIBERT et Armand COMPAROT
Les sources de ce logiciel sont libre et gratuite.
Toutes personnes ayant utilisé ce logiciel peut me donner son avis pour l'améliorer ou simplement dire son avis sur le forum du site http://protecinfo.redheberg.com .
*/
#include <QApplication>
#include <QTranslator>
#include <QTextCodec>
#include "FenPrincipale.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
/*  décommenter pour la traduction en anglais
    QTranslator translator;
    translator.load("qtprojet_en");
    app.installTranslator(&translator);
*/
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        
    FenPrincipale fenetre;
    fenetre.show();
 
    return app.exec();
}

