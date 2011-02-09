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
#include <iostream>
#include <string>
#include <gmpxx.h>
 
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
    QMenu *menuFichier;
    QMenu *menuEdition;
    QMenu *menuAffichage;
    QStatusBar *barreEtat;
};
 
#endif

