/*
Ce logiciel fut réaliser par Alexandre GAY avec la colaboration de Thomas MIJIEUX, Robin PHILIBERT et Armand COMPAROT
Les sources de ce logiciel sont libre et gratuite.
Toutes personnes ayant utilisé ce logiciel peut me donner son avis pour l'améliorer ou simplement dire son avis sur le forum du site http://protecinfo.redheberg.com .
*/
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QTextCodec>
#include "FenRsa-encoding.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString language = "fr";
    QFile file( "language" );

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        language = in.readAll();
        language = "trRsa-encoding_" + language + ".qm";
        file.close();
    }

    else
    {
        if (file.open(QIODevice::WriteOnly| QIODevice::Text))
        {
            QTextStream out(&file);
            out << "fileNotFound";
        }
        file.close();
    }
    
    QTranslator translator;
    translator.load(language);
    app.installTranslator(&translator);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    FenPrincipale fenetre;
    fenetre.show();

    return app.exec();
}

