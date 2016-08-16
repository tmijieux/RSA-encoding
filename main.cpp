/*
  Ce logiciel fut réalisé par Alexandre GAY
*/
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QTextCodec>
#include "RSAMainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString language("fr");
    QFile file("language");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        language = in.readAll();
        language = "trRsa-encoding_" + language + ".qm";
        file.close();
    } else {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "fileNotFound";
        }
        file.close();
    }

    QTranslator translator;
    translator.load(language);
    app.installTranslator(&translator);

    /*
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    */

    RSA::Window win;
    win.show();

    return app.exec();
}
