#include "FenPrincipale.h"
#include "FenApropos.h"
#include "FenAide.h"

using namespace std;

FenPrincipale::FenPrincipale()
{
    setWindowTitle("RSA-encoding");

    //MENU
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");
    QAction *actionQuitter = menuFichier->addAction("&Quitter");
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    QMenu *menuAide = menuBar()->addMenu("&Aide");
    QAction *aide = menuAide->addAction("aide");
    connect(aide, SIGNAL(triggered()), this, SLOT(aideFen()));
    aide->setShortcut(QKeySequence("F1"));
    QAction *aproposSoft = menuAide->addAction("Apropos");
    connect(aproposSoft, SIGNAL(triggered()), this, SLOT(aproposSoftware()));
    QAction *aproposQT = menuAide->addAction("Apropos Qt");
    connect(aproposQT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    //QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    
    
    //BAR_ETAT
    barreEtat = statusBar();
    actionQuitter->setStatusTip("Quitte le programme");
    aproposSoft->setStatusTip("apropos du logiciel");
    aproposQT->setStatusTip("apropos de Qt");


    //ZONECENTRALE
    zoneCentrale = new QWidget;
    zoneCentrale->setFixedSize(540, 560);
    onglets = new QTabWidget(zoneCentrale);
    
    page1 = new QWidget;
    page2 = new QWidget;
  
    //Partie crypter
    crypter = new QPushButton("Crypter", this);
    crypter->setFont(QFont("Comic Sans MS", 14));
    connect(crypter, SIGNAL(released()), this,SLOT(crypter_show()));
    connect(crypter, SIGNAL(clicked()), this , SLOT(f_cryper()));
    
    cle_e = new QLineEdit(this);
    cle_n = new QLineEdit(this);
    message_a_crypter = new QTextEdit(this);
    message_crypter = new QTextEdit(this);
    message_crypter->setReadOnly(true);
    
    enter_cle_e = new QLabel("entrez la clé e : ", this);
    enter_cle_n = new QLabel("entrez la clé n : ", this);
    enter_text = new QLabel("entrez le message à crypter : ", this);
    text_crypte = new QLabel("voici le message crypté : ", this);
    
    gbox1 = new  QGridLayout;
    gbox1->addWidget(enter_cle_e, 0, 0);
    gbox1->addWidget(cle_e, 0, 1, 1, 2);
    gbox1->addWidget(enter_cle_n, 1, 0);
    gbox1->addWidget(cle_n, 1, 1, 1, 2);
    gbox1->addWidget(enter_text, 2, 0);
    gbox1->addWidget(message_a_crypter, 2, 1, 1, 2);
    gbox1->addWidget(text_crypte, 3, 0);
    gbox1->addWidget(message_crypter, 3, 1, 1, 2);
    gbox1->addWidget(crypter, 4, 1, 1, 2);
        
    //Partie decrypter
    decrypter = new QPushButton("Décrypter", this);
    decrypter->setFont(QFont("Comic Sans MS", 14));
    decrypter->move(110, 100);
    connect(decrypter, SIGNAL(clicked()), this , SLOT(f_decrypter()));
    connect(decrypter, SIGNAL(released()), this , SLOT(decrypter_show()));
    
    cle_d = new QLineEdit(this);
    cle_n2 = new QLineEdit(this);
    message_crypte = new QTextEdit(this);
    message_decrypte = new QTextEdit(this);
    message_decrypte->setReadOnly(true);
    
    enter_cle_d = new QLabel("entrez la clé d : ", this);
    enter_cle_n = new QLabel("entrez la clé n : ", this);
    enter_text = new QLabel("entrez le message crypté : ", this);
    text_crypte = new QLabel("voici le message decrypté : ", this);
    
    gbox2 = new  QGridLayout;
    gbox2->addWidget(enter_cle_d, 0, 0);
    gbox2->addWidget(cle_d, 0, 1, 1, 2);
    gbox2->addWidget(enter_cle_n, 1, 0);
    gbox2->addWidget(cle_n2, 1, 1, 1, 2);
    gbox2->addWidget(enter_text, 2, 0);
    gbox2->addWidget(message_crypte, 2, 1, 1, 2);
    gbox2->addWidget(text_crypte, 3, 0);
    gbox2->addWidget(message_decrypte, 3, 1, 1, 2);
    gbox2->addWidget(decrypter, 4, 1, 1, 2);
        
    
    //Partie Generale assemblage
    page1->setLayout(gbox1);
    page2->setLayout(gbox2);
    
    onglets->addTab(page1, "crypter");
    onglets->addTab(page2, "décrypter");
    
    setCentralWidget(zoneCentrale);
}


void FenPrincipale::f_cryper()
{
    string message_initial = message_a_crypter->toPlainText().toStdString();
    
    unsigned int i = 0;
	
	try
    {
	    mpz_class message_crypte1, e(cle_e->text().toStdString()), n(cle_n->text().toStdString()), message_claire;
    
        if (e == 0 && n ==0)
        {
	        n = 8051;
	        e = 79;
	    }
	
	    message_crypter->clear();
    
    
	    for (i=0; i < message_initial.size(); i++)
	    {
	    	message_claire =  message_initial[i];
	    	mpz_powm (message_crypte1.get_mpz_t() , message_claire.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t() );

            message_crypter->insertPlainText(message_crypte1.get_str().data());
            message_crypter->insertPlainText(" ");
    	}
    }
    
    catch(...)
    {
    QMessageBox::warning(this, "erreur", "Un probleme est survenue, vérifiez la clé et que vous avez entrez un texte à crypter !");
    }    
}

void FenPrincipale::f_decrypter()
{
    string message_crypte_entre = message_crypte->toPlainText().toStdString();

    int espace = 0;
	int mot = 1;
	int i = 0;
	QString message_final;
	
	
	try
    {
	    mpz_class d(cle_d->text().toStdString()), message_claire, message_crypte_caract, n(cle_n2->text().toStdString());

        if (d == 0 && n ==0)    
        {
	        n = 8051;
	        d = 4783;
    	}

	    while ( message_crypte_entre[i] != '\0' )
	    {
	    	if ( message_crypte_entre[i] == ' ')
	    	mot++;
	        i++;
	    }
	
        message_decrypte->clear();

    
    	for ( i=0; i < mot ; i++)
	    {
    		espace = message_crypte_entre.find(" ");

	    	message_crypte_caract = message_crypte_entre.substr(0, espace);
	    	message_crypte_entre.erase(0, (espace + 1));

	    	mpz_powm (message_claire.get_mpz_t(), message_crypte_caract.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t() );

    		message_final = message_claire.get_d();  
            message_decrypte->insertPlainText(message_final);
     	}
    }
    
    catch(...)
    {
        QMessageBox::warning(this, "erreur", "un probleme vient de se produire il se peut que ce soit: \n \t - vos clés qui sont incorrectes \n \t - votre message crypté qui comporte une erreur (verifier  s'il y a un espace avant ou apres le dernier nombre, si oui: l'enlever)");
    }        
}

void FenPrincipale::crypter_show()
{
    barreEtat->showMessage("Crypte", 2000);
}

void FenPrincipale::decrypter_show()
{
    barreEtat->showMessage("Decrypte", 2000);
}

void FenPrincipale::aproposSoftware()
{
    FenApropos *fenetreApropos = new FenApropos(this);
    fenetreApropos->exec();
}

void FenPrincipale::aideFen()
{
    FenAide *fenetreAide = new FenAide(this);
    fenetreAide->exec();
}
