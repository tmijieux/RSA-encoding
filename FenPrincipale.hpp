#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QApplication>
#include <QWidget>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QPushButton>
#include <QFont>
#include <QTabWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QMessageBox>
#include <QProgressBar>
#include <iostream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <gmpxx.h>

#include "KeyGenPanel.hpp"

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

public:
    FenPrincipale();

public slots:
    void f_crypter();
    void f_decrypter();
    void f_cle();

    void aproposSoftware();
    void aideFen();
    
    void englishTranslate();
    void frenchTranslate();
    void checkLang();
    
    void fileNotFound();
    
    void add_encrypt_status();
    void remove_encrypt_status();
    
    void add_decrypt_status();
    void remove_decrypt_status();

    void add_keygen_status();
    void remove_keygen_status();
    
signals:
    void encrypt_end();
    void decrypt_end();
    void keygen_end();

private:
    void setup_menu();
    void setup_status_bar();
    QWidget *setup_decrypt_panel();
    QWidget *setup_encrypt_panel();
    QWidget *setup_keygen_panel();
    void setup_global_layout(QWidget *p1, QWidget *p2, QWidget *p3);

    KeyGenPanel keyGenPanel;
    
    QWidget *zoneCentrale;

    QLabel *enter_cle_n;
    QLabel *enter_cle_d;
    QLabel *enter_cle_e;
    QLabel *enter_text;
    QLabel *text_crypte;

    QPushButton *encrypt_pbutton;
    QPushButton *decrypt_pbutton;


    QTabWidget *onglets;

    QLineEdit *cle_n;
    QLineEdit *cle_n2;
    QLineEdit *cle_d;
    QLineEdit *cle_e;

    QTextEdit *message_a_crypter;
    QTextEdit *message_crypter;
    QTextEdit *message_crypte;
    QTextEdit *message_decrypte;

    QStatusBar *status_bar;
    QAction *checkEnglish;
    QAction *checkFrench;
    QAction *actionQuitter;
    QAction *aide;
    QAction *aproposSoft;
    QAction *aproposQT;

    QActionGroup *language;

    QMenu *menuFichier;
    QMenu *menuLang;
    QMenu *menuAide;

    QLabel *encrypt_status_label;
    QLabel *decrypt_status_label;
    QLabel *keygen_status_label;

    unsigned int decrypt_mot;
    unsigned int encrypt_mot;
};

#endif //FENPRINCIPALE_H
