#include "FenRsa-encoding.h"

using namespace std;

FenPrincipale::FenPrincipale()
{
    setWindowTitle("RSA-encoding");


    //MENU
    menuFichier = new QMenu;
    menuFichier = menuBar()->addMenu(tr("&Fichier"));
    actionQuitter = new QAction(this);
    actionQuitter = menuFichier->addAction(tr("&Quitter"));
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    menuLang = new QMenu;
    menuLang = menuFichier->addMenu(tr("&Langues"));

    checkEnglish = new QAction(this);
    checkEnglish = menuLang->addAction("english");
    checkEnglish->setCheckable(true);
    connect(checkEnglish, SIGNAL(triggered()), this, SLOT(englishTranslate()));

    checkFrench = new QAction(this);
    checkFrench = menuLang->addAction("francais");
    checkFrench->setCheckable(true);
    connect(checkFrench, SIGNAL(triggered()), this, SLOT(frenchTranslate()));
    checkLang();

    QMenu *menuAide = menuBar()->addMenu(tr("&Aide"));
    QAction *aide = menuAide->addAction(tr("aide"));
    connect(aide, SIGNAL(triggered()), this, SLOT(aideFen()));
    aide->setShortcut(QKeySequence("F1"));
    QAction *aproposSoft = menuAide->addAction(tr("Apropos"));
    connect(aproposSoft, SIGNAL(triggered()), this, SLOT(aproposSoftware()));
    QAction *aproposQT = menuAide->addAction(tr("Apropos Qt"));
    connect(aproposQT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    //QMenu *menuAffichage = menuBar()->addMenu("&Affichage");


    //BAR_ETAT
    barreEtat = statusBar();
    fileNotFound();
    actionQuitter->setStatusTip(tr("Quitte le programme"));
    aproposSoft->setStatusTip(tr("apropos du logiciel"));
    aproposQT->setStatusTip(tr("apropos de Qt"));
    aide->setStatusTip(tr("aide du logiciel"));
    checkEnglish->setStatusTip(tr("traduit le logiciel en anglais"));
    checkFrench->setStatusTip(tr("le logiciel est en francais"));

    //ZONECENTRALE
    zoneCentrale = new QWidget;
    zoneCentrale->setFixedSize(540, 560);
    onglets = new QTabWidget(zoneCentrale);

    page1 = new QWidget;
    page2 = new QWidget;

    //Partie crypter
    crypter = new QPushButton(tr("Crypter"), this);
    crypter->setFont(QFont("Comic Sans MS", 14));
    connect(crypter, SIGNAL(released()), this,SLOT(crypter_show()));
    connect(crypter, SIGNAL(clicked()), this , SLOT(f_cryper()));
    connect(this, SIGNAL(encrypt100()), this, SLOT(encrypt_nb()));

    cle_e = new QLineEdit(this);
    cle_n = new QLineEdit(this);
    message_a_crypter = new QTextEdit(this);
    message_crypter = new QTextEdit(this);
    message_crypter->setReadOnly(true);

    enter_cle_e = new QLabel(tr("entrez la clé e : "), this);
    enter_cle_n = new QLabel(tr("entrez la clé n : "), this);
    enter_text = new QLabel(tr("entrez le message à crypter : "), this);
    text_crypte = new QLabel(tr("voici le message crypté : "), this);

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
    decrypter = new QPushButton(tr("Décrypter"), this);
    decrypter->setFont(QFont("Comic Sans MS", 14));
    decrypter->move(110, 100);

    connect(decrypter, SIGNAL(clicked()), this , SLOT(f_decrypter()));
    connect(decrypter, SIGNAL(released()), this , SLOT(decrypter_show()));
    connect(this, SIGNAL(decrypt100()), this, SLOT(decrypt_nb()));


    cle_d = new QLineEdit(this);
    cle_n2 = new QLineEdit(this);
    message_crypte = new QTextEdit(this);
    message_decrypte = new QTextEdit(this);
    message_decrypte->setReadOnly(true);

    enter_cle_d = new QLabel(tr("entrez la clé d : "), this);
    enter_cle_n = new QLabel(tr("entrez la clé n : "), this);
    enter_text = new QLabel(tr("entrez le message crypté : "), this);
    text_crypte = new QLabel(tr("voici le message decrypté : "), this);

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

    onglets->addTab(page1, tr("crypter"));
    onglets->addTab(page2, tr("décrypter"));



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

        encrypt_mot = message_initial.size();

	    for (i=0; i < encrypt_mot; i++)
	    {
	    	message_claire =  message_initial[i];
	    	mpz_powm (message_crypte1.get_mpz_t() , message_claire.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t() );
            message_crypter->insertPlainText(message_crypte1.get_str().data());
            
            if (i < encrypt_mot - 1)
            message_crypter->insertPlainText(" ");
    	    
    	    emit encrypt100();
    	}
    }

    catch(...)
    {
    QMessageBox::warning(this, tr("erreur"), tr("Un probleme est survenue, vérifiez la clé et que vous avez entrez un texte à crypter !"));
    }

    emit finEncrypt();
}

void FenPrincipale::f_decrypter()
{
    string message_crypte_entre = message_crypte->toPlainText().toStdString();

    int espace = 0;
	decrypt_mot = 1;
	unsigned int i = 0;
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
	    	decrypt_mot++;
	        i++;
	    }

        message_decrypte->clear();


    	for ( i=0; i < decrypt_mot ; i++)
	    {
    		espace = message_crypte_entre.find(" ");

	    	message_crypte_caract = message_crypte_entre.substr(0, espace);
	    	message_crypte_entre.erase(0, (espace + 1));

	    	mpz_powm (message_claire.get_mpz_t(), message_crypte_caract.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t() );

    		message_final = message_claire.get_d();
            message_decrypte->insertPlainText(message_final);
            emit decrypt100();
     	}
    }

    catch(...)
    {
        QMessageBox::warning(this, tr("erreur"), tr("un probleme vient de se produire il se peut que ce soit: \n \t - vos clés qui sont incorrectes \n \t - votre message crypté qui comporte une erreur (verifier  s'il y a un espace avant le premier nombre ou apres le dernier, si oui: l'enlever)"));
    }

    emit finDecrypt();
}

void FenPrincipale::crypter_show()
{
    encrypt_bloc = 0;
    encrypt_msg = new QLabel(tr("cryptage en cours"));
    encrypt_msg->setAlignment(Qt::AlignLeft);

    encrypt_lcd = new QProgressBar(this);
    encrypt_lcd->setMaximumHeight(15);
    encrypt_lcd->setGeometry(200, 0, 150, 18);
    encrypt_lcd->setValue(0);

    barreEtat->addWidget(encrypt_msg);
    barreEtat->addWidget(encrypt_lcd);

    connect(this, SIGNAL(finEncrypt()), this, SLOT(rmEtatEncrypt()));
}

void FenPrincipale::decrypter_show()
{
    decrypt_bloc = 0;
    decrypt_msg = new QLabel(tr("décryptage en cours"));
    decrypt_msg->setAlignment(Qt::AlignLeft);

    decrypt_lcd = new QProgressBar(this);
    decrypt_lcd->setMaximumHeight(15);
    decrypt_lcd->setGeometry(200, 0, 150, 18);
    decrypt_lcd->setValue(0);

    barreEtat->addWidget(decrypt_msg);
    barreEtat->addWidget(decrypt_lcd);

    connect(this, SIGNAL(finDecrypt()), this, SLOT(rmEtatDecrypt()));
}

void FenPrincipale::decrypt_nb()
{
    decrypt_bloc ++;
    int pourCent;
    pourCent = (decrypt_bloc * 100) / decrypt_mot;
    decrypt_lcd->setValue(pourCent);
}

void FenPrincipale::rmEtatDecrypt()
{
    barreEtat->removeWidget(decrypt_msg);
    barreEtat->removeWidget(decrypt_lcd);
    barreEtat->showMessage(tr("Le message a été décrypté"), 3500);
}


void FenPrincipale::encrypt_nb()
{
    encrypt_bloc ++;
    int pourCent;
    pourCent = (encrypt_bloc * 100) / encrypt_mot;
    encrypt_lcd->setValue(pourCent);
}

void FenPrincipale::rmEtatEncrypt()
{
    barreEtat->removeWidget(encrypt_msg);
    barreEtat->removeWidget(encrypt_lcd);
    barreEtat->showMessage(tr("Le message a été crypté"), 3500);
}


void FenPrincipale::aproposSoftware()
{
    QMessageBox::information(this, tr("Apropos"), tr("<p>Ce programme fut réalisé par Alexandre GAY avec le soutien d'Armand Comparot, de Thomas Mijieux et de Robin PHILIBERT.</p> <p>Les codes sources sont libre et gratuit, vous pouvez les retrouver sur le site à l'addresse <a href='http://protecinfo.redheberg.com'>protecinfo.redheberg</a> .</p> <p>Vous trouverez sur le site une page forum ou vous pourez donner votre avis sur le logiciel.</p> <p>Pour plus d'information n'hésitez pas à nous contacter sur le site ou par mail</p> <p>Merci d'utiliser notre logiciel.</p>"));
}

void FenPrincipale::aideFen()
{
    QMessageBox::information(this,tr("Aide"), tr("<p>Pour utiliser ce logiciel il vous suffit de rentrer les clés public (e, n) et le message secret à transmetre pour crypter un message et de rentrer les clés privé (d, n) et le message crypté pour le décrypter !</p> <p>Si vous n'avez pas de clé, vous pouvez faire des tests en utilisant comme clé public (0, 0) et comme clé prive (0, 0). Ces clé seront automatiquement remplacé par des clés valides.</p> <p>Bonne utilisation !</p>"));
}

void FenPrincipale::frenchTranslate()
{
    checkEnglish->setChecked(false);
    checkFrench->setChecked(true);

    QString language;
    QFile file("language");
    if (file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        language = in.readAll();
    }
    file.close();

    if (language != "fr")
    {
        if (!file.open(QIODevice::WriteOnly| QIODevice::Text))
        QMessageBox::critical(this, tr("erreur fichier"), tr("le fichier language n'a pas put s'ouvrire en ecriture"));

        QTextStream out(&file);
        out << "fr";
        QMessageBox::information(this, "langue", "vous devez maintenant redémarrer le programme pour que celui ci soit en français");
    }
    file.close();
}

void FenPrincipale::englishTranslate()
{
    checkFrench->setChecked(false);
    checkEnglish->setChecked(true);

    QString language;
    QFile file("language");
    if (file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        language = in.readAll();
    }
    file.close();

    if (language != "en")
    {
        if (!file.open(QIODevice::WriteOnly| QIODevice::Text))
        QMessageBox::critical(this, tr("erreur fichier"), tr("le fichier language n'a pas put s'ouvrire en ecriture"));

        QTextStream out(&file);
        out << "en";
        QMessageBox::information(this, "language", "you must now restart the program to have it in english");
    }
    file.close();
}

void FenPrincipale::checkLang()
{
    QString language;
    QFile file("language");
    if (file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        language = in.readAll();
    }
    file.close();

    if (language == "en")
    {
        checkFrench->setChecked(false);
        checkEnglish->setChecked(true);
    }

    else
    {
        checkFrench->setChecked(true);
        checkEnglish->setChecked(false);
    }
}

void FenPrincipale::fileNotFound()
{
    QString notFound;
    QFile file("language");
    if (file.open(QFile::ReadOnly))
    {
        QTextStream in(&file);
        notFound = in.readAll();
    }
    file.close();

    if (notFound == "fileNotFound")
    {
        barreEtat->showMessage(tr("fichier language introuvable, la langue par defaut a été généré"), 3500);
         if (file.open(QIODevice::WriteOnly| QIODevice::Text))
        {
            QTextStream out(&file);
            out << "fr";
        }
        file.close();
    }
}

