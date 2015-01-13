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
#include <vector>

class FenPrincipale : public QMainWindow
{
	Q_OBJECT

public:
	FenPrincipale();

public slots:
	void f_crypter();
	void f_decrypter();
	void f_cle();
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
	void creat_cle_show();

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
	QLabel *cleN;
	QLabel *cleE;
	QLabel *cleD;
	QPushButton *crypter;
	QPushButton *decrypter;
	QPushButton *cle;
	QTabWidget *onglets;
	QWidget *page1;
	QWidget *page2;
	QWidget *page3;
	QGridLayout *gbox1;
	QGridLayout *gbox2;
	QGridLayout *gbox3;
	
	QLineEdit *cle_n;
	QLineEdit *cle_n2;
	QLineEdit *cle_d;
	QLineEdit *cle_e;
	
	QTextEdit *message_a_crypter;
	QTextEdit *message_crypter;
	QTextEdit *message_crypte;
	QTextEdit *message_decrypte;
	
	QTextEdit *affiche_cleN;
	QTextEdit *affiche_cleE;
	QTextEdit *affiche_cleD;
	
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
	QLabel *creat_cle;
	
	unsigned int decrypt_bloc;
	unsigned int decrypt_mot;
	unsigned int encrypt_bloc;
	unsigned int encrypt_mot;
};

#endif

