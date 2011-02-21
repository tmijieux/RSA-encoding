#ifndef DEF_FENPRINCIPALE
#define DEF_FENPRINCIPALE

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
#include <gmpxx.h>
#include <QFile>
#include <QTextStream>

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
    FenPrincipale();

    public slots:
     void f_cryper();
     void f_decrypter();
     void crypter_show();
     void decrypter_show();
     void aproposSoftware();
     void aideFen();
     void englishTranslate();
     void frenchTranslate();
     void checkLang();
     void fileNotFound();
     void decrypt_nb();
     void rmEtatDecrypt();
     void encrypt_nb();
     void rmEtatEncrypt();

     signals:
     void decrypt100();
     void finDecrypt();
     void encrypt100();
     void finEncrypt();

    private:
    QWidget *zoneCentrale;
    QLabel *enter_cle_n;
    QLabel *enter_cle_d;
    QLabel *enter_cle_e;
    QLabel *enter_text;
    QLabel *text_crypte;
    QPushButton *crypter;
    QPushButton *decrypter;
    QTabWidget *onglets;
    QWidget *page1;
    QWidget *page2;
    QGridLayout *gbox1;
    QGridLayout *gbox2;
    QLineEdit *cle_n;
    QLineEdit *cle_n2;
    QLineEdit *cle_d;
    QLineEdit *cle_e;
    QTextEdit *message_a_crypter;
    QTextEdit *message_crypter;
    QTextEdit *message_crypte;
    QTextEdit *message_decrypte;
    QStatusBar *barreEtat;
    QAction *checkEnglish;
    QAction *checkFrench;
    QAction *actionQuitter;
    QActionGroup *language;
    QMenu *menuFichier;
    QMenu *menuLang;
    QProgressBar *encrypt_lcd;
    QProgressBar *decrypt_lcd;
    QLabel *encrypt_msg;
    QLabel *decrypt_msg;
    unsigned int decrypt_bloc;
    unsigned int decrypt_mot;
    unsigned int encrypt_bloc;
    unsigned int encrypt_mot;
};

#endif

