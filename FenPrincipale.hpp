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
	void decrypt_100();
	void decrypt_end();

	void encrypt_100();
	void encrypt_end();

private:
        void setup_menu();
        void setup_status_bar();
        QWidget *setup_decrypt_panel();
        QWidget *setup_encrypt_panel();
        QWidget *setup_keygen_panel();
        void setup_global_layout(QWidget *p1, QWidget *p2, QWidget *p3);

	QWidget *zoneCentrale;

	QLabel *enter_cle_n;
	QLabel *enter_cle_d;
	QLabel *enter_cle_e;
	QLabel *enter_text;
	QLabel *text_crypte;
	QLabel *cleN;
	QLabel *cleE;
	QLabel *cleD;

	QPushButton *crypt_pbutton;
	QPushButton *decrypt_pbutton;
	QPushButton *keygen_pbutton;

	QTabWidget *onglets;

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

#endif //FENPRINCIPALE_H
