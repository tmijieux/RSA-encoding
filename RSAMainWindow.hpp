#ifndef RSAMAINWINDOW_H
#define RSAMAINWINDOW_H

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

class RSAMainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *central_widget;

    QStatusBar *status_bar;
    QMenuBar *menu_bar;

    KeyGenPanel *keyGenPanel;
    EncryptPanel *encryptPanel;
    DecryptPanel *decryptPanel;

    QAction *checkEnglish;
    QAction *checkFrench;

    void setup_menu();

public:
    RSAMainWindow();

public slots:
    void apropos_software();
    void help_message();
    void english_translate();
    void french_translate();
    void check_lang();
    void file_not_found();
};

#endif //RSAMAINWINDOW_H
