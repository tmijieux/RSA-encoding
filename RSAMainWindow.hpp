#ifndef RSA_MAINWINDOW_H
#define RSA_MAINWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

#include <QTabWidget>
#include <QGridLayout>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <string>
#include <vector>
#include <gmpxx.h>

#include "KeyGenPanel.hpp"
#include "EncryptPanel.hpp"
#include "DecryptPanel.hpp"

#define _(x) tr((x))

namespace RSA {

class Window : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *_centralWidget;
    QStatusBar *_statusBar;
    QMenuBar *_menuBar;

    KeyGenPanel *_keyGenPanel;
    EncryptPanel *_encryptPanel;
    DecryptPanel *_decryptPanel;

    QAction *_checkEnglish;
    QAction *_checkFrench;

    void SetupMenu();
    void TranslateTo(QString const &lang);

public:
    Window();

public slots:
    void DisplayApropos();
    void DisplayHelp();
    void TranslateToEnglish();
    void TranslateToFrench();
    void CheckLang();
    void CheckLangFile();
};

}; // end namespace RSA;

#endif //RSA_MAINWINDOW_H
