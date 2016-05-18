#include "FenPrincipale.hpp"

#include "f_crypter.cpp"
#include "f_decrypter.cpp"
#include "f_cle.cpp"


void FenPrincipale::setup_menu()
{
	//MENU
	this->menuFichier = menuBar()->addMenu(tr("&Fichier"));
	this->actionQuitter = menuFichier->addAction(tr("&Quitter"));

	connect(this->actionQuitter, SIGNAL(triggered()),
                qApp,                SLOT(quit())
        );
	this->actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

	// LANGAGE
	this->menuLang = this->menuFichier->addMenu(tr("&Langues"));
	this->checkEnglish = menuLang->addAction("english");
	this->checkEnglish->setCheckable(true);
	connect(this->checkEnglish, SIGNAL(triggered()),
		this,               SLOT(englishTranslate()));

	this->checkFrench = menuLang->addAction("français");
	this->checkFrench->setCheckable(true);
	connect(this->checkFrench, SIGNAL(triggered()),
		this,              SLOT(frenchTranslate()));
	this->checkLang();
	// FIN LANGAGE

	// AIDE
        this->menuAide = menuBar()->addMenu(tr("&Aide"));
	this->aide = this->menuAide->addAction(tr("aide"));
	this->aide->setShortcut(QKeySequence("F1"));
	connect(this->aide, SIGNAL(triggered()),
		this,       SLOT(aideFen()));

        this->aproposSoft = this->menuAide->addAction(tr("Apropos"));
	connect(this->aproposSoft, SIGNAL(triggered()),
		this, SLOT(aproposSoftware()));

	this->aproposQT = menuAide->addAction(tr("Apropos Qt"));
	connect(this->aproposQT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	// QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
	// FIN AIDE

}

QWidget *FenPrincipale::setup_decrypt_panel()
{
        QWidget *page = new QWidget();
        QGridLayout *box = new QGridLayout();
        
	decrypt_pbutton = new QPushButton(tr("Décrypter"), this);
	decrypt_pbutton->setFont(QFont("Comic Sans MS", 14));
	//decrypt_pbutton->move(110, 100);

	connect(decrypt_pbutton, SIGNAL(  clicked()       ),
                this,            SLOT  (  f_decrypter()   )
        );
	connect(decrypt_pbutton, SIGNAL( released()        ),
                this,            SLOT  ( decrypter_show()  )
        );
	connect(this, SIGNAL(  decrypt_100()  ),
                this, SLOT  (  decrypt_nb()   )
        );

	this->cle_d = new QLineEdit(this);
	this->cle_n2 = new QLineEdit(this);
	this->message_crypte = new QTextEdit(this);
	this->message_decrypte = new QTextEdit(this);
	this->message_decrypte->setReadOnly(true);

	this->enter_cle_d = new QLabel(tr("entrez la clé d : "), this);
	this->enter_cle_n = new QLabel(tr("entrez la clé n : "), this);
	this->enter_text = new QLabel(tr("entrez le message crypté : "), this);
	this->text_crypte = new QLabel(tr("voici le message decrypté : "), this);

	box->addWidget(this->enter_cle_d, 0, 0);
	box->addWidget(this->cle_d, 0, 1, 1, 2);
	box->addWidget(this->enter_cle_n, 1, 0);
	box->addWidget(this->cle_n2, 1, 1, 1, 2);
	box->addWidget(this->enter_text, 2, 0);
	box->addWidget(this->message_crypte, 2, 1, 1, 2);
	box->addWidget(this->text_crypte, 3, 0);
	box->addWidget(this->message_decrypte, 3, 1, 1, 2);
	box->addWidget(decrypt_pbutton, 4, 1, 1, 2);

        page->setLayout(box);
        return page;
}


QWidget *FenPrincipale::setup_keygen_panel()
{
        QWidget *page = new QWidget();
        QGridLayout *box = new QGridLayout();
        
	//Partie generateur de cles
	keygen_pbutton = new QPushButton(tr("générer les clés"), this);
	keygen_pbutton->setFont(QFont("Comic Sans MS", 14));

	connect(keygen_pbutton, SIGNAL(  clicked() ),
                this,           SLOT  (  f_cle()   )
        );
	connect(keygen_pbutton, SIGNAL(  released()       ),
                this,           SLOT  (  creat_cle_show() )
        );

	this->affiche_cleN = new QTextEdit(this);
	this->affiche_cleE = new QTextEdit(this);
	this->affiche_cleD = new QTextEdit(this);
	this->affiche_cleN->setReadOnly(true);
	this->affiche_cleE->setReadOnly(true);
	this->affiche_cleD->setReadOnly(true);

	this->cleN = new QLabel(tr("Voici la cle N : "), this);
	this->cleE = new QLabel(tr("Voici la cle E : "), this);
	this->cleD = new QLabel(tr("Voici la cle D : "), this);

	box->addWidget(keygen_pbutton, 0, 1, 1, 2);
	box->addWidget(this->cleN, 1, 0);
	box->addWidget(this->cleE, 2, 0);
	box->addWidget(this->cleD, 3, 0);
	box->addWidget(this->affiche_cleN, 1, 1, 2, 2);
	box->addWidget(this->affiche_cleE, 2, 1, 2, 2);
	box->addWidget(this->affiche_cleD, 3, 1, 2, 2);
        
        page->setLayout(box);
        return page;
        
}

QWidget *FenPrincipale::setup_encrypt_panel()
{
        QWidget *page = new QWidget();
        QGridLayout *box = new QGridLayout();
        
	crypt_pbutton = new QPushButton(tr("Crypter"), this);
	crypt_pbutton->setFont(QFont("Comic Sans MS", 14));
        
	connect(crypt_pbutton, SIGNAL(  released()     ),
                this,          SLOT  (  crypter_show() )
        );
	connect(crypt_pbutton, SIGNAL(  clicked()   ),
                this,          SLOT  (  f_crypter() )
        );        
	connect(this, SIGNAL(  encrypt_100() ),
                this, SLOT  (  encrypt_nb()  )
        );

	this->cle_e = new QLineEdit(this);
	this->cle_n = new QLineEdit(this);
	this->message_a_crypter = new QTextEdit(this);
	this->message_crypter = new QTextEdit(this);
	this->message_crypter->setReadOnly(true);

	this->enter_cle_e = new QLabel(tr("entrez la clé e : "), this);
	this->enter_cle_n = new QLabel(tr("entrez la clé n : "), this);
	this->enter_text = new QLabel(
                tr("entrez le message à crypter : "), this);
	this->text_crypte = new QLabel(tr("voici le message crypté : "), this);

	box = new QGridLayout();
	box->addWidget(this->enter_cle_e, 0, 0);
	box->addWidget(this->cle_e, 0, 1, 1, 2);
	box->addWidget(this->enter_cle_n, 1, 0);
	box->addWidget(this->cle_n, 1, 1, 1, 2);
	box->addWidget(this->enter_text, 2, 0);
	box->addWidget(this->message_a_crypter, 2, 1, 1, 2);
	box->addWidget(this->text_crypte, 3, 0);
	box->addWidget(this->message_crypter, 3, 1, 1, 2);
	box->addWidget(this->crypt_pbutton, 4, 1, 1, 2);

        page->setLayout(box);
        return page;
}


void FenPrincipale::setup_status_bar()
{
	status_bar = statusBar();
	this->fileNotFound();
        
	actionQuitter->setStatusTip(tr("Quitte le programme"));
	aproposSoft->setStatusTip(tr("apropos du logiciel"));
	aproposQT->setStatusTip(tr("apropos de Qt"));
	aide->setStatusTip(tr("aide du logiciel"));
	checkEnglish->setStatusTip(tr("traduit le logiciel en anglais"));
	checkFrench->setStatusTip(tr("le logiciel est en francais"));
}


void FenPrincipale::setup_global_layout(QWidget *p1, QWidget *p2, QWidget *p3)
{
        onglets = new QTabWidget(zoneCentrale);
	onglets->addTab(p1, tr("crypter"));
	onglets->addTab(p2, tr("décrypter"));
	onglets->addTab(p3, tr("cle"));
}

FenPrincipale::FenPrincipale()
{
	setWindowTitle("RSA-encoding");
	zoneCentrale = new QWidget();
	zoneCentrale->setFixedSize(540, 560);
	setCentralWidget(zoneCentrale);

        setup_menu();
        setup_status_bar();
        
        setup_global_layout(
                setup_encrypt_panel(),
                setup_decrypt_panel(),
                setup_keygen_panel()
        );
}

void FenPrincipale::aproposSoftware()
{
        const char *msg;
        msg = "<p>Ce programme fut réalisé par Alexandre GAY avec le "
                "soutien d'Armand Comparot, de Thomas Mijieux et de Robin "
                "PHILIBERT.</p><p>Le code source est libre et gratuit, vous "
                "pouvez le retrouver sur le site à l'adresse "
                "<a href='http://protecinfo.redheberg.com'>"
                "protecinfo.redheberg</a> .</p> <p>Vous trouverez sur le "
                "site une page forum ou vous pourez donner votre avis sur "
                "le logiciel.</p> <p>Pour plus d'information n'hésitez pas "
                "à nous contacter sur le site ou par mail</p>"
                " <p>Merci d'utiliser notre logiciel.</p>";
	QMessageBox::information(this, tr("Apropos"), tr(msg));
}

void FenPrincipale::aideFen()
{
        const char *msg;
        msg = "<p>Pour utiliser ce logiciel il vous suffit de rentrer la "
                "clé publique (e, n) et le message secret à transmettre "
                "pour crypter un message et de rentrer la clé privée (d, n) "
                "et le message crypté pour le décrypter ! </p> <p>Si vous "
                "n'avez pas de clé, vous pouvez faire des tests en "
                "utilisant comme clé public (0, 0) et comme clé prive "
                "(0, 0). Ces clés seront automatiquement remplacé par "
                "des clés valides.</p> <p>Bonne utilisation !</p>";
        QMessageBox::information(this,tr("Aide"), tr(msg));
}

void FenPrincipale::frenchTranslate()
{
	this->checkEnglish->setChecked(false);
	this->checkFrench->setChecked(true);

	QString language;
	QFile file("language");
	if (file.open(QFile::ReadOnly)) {
		QTextStream in(&file);
		language = in.readAll();
	}
	file.close();

	if (language != "fr") {
		if (!file.open(QIODevice::WriteOnly| QIODevice::Text))
			QMessageBox::critical(this, tr("erreur fichier"),
					      tr("le fichier language n'a pas"
						 " pu s'ouvrir en ecriture"));
		QTextStream out(&file);
		out << "fr";
		QMessageBox::information(this, "langue",
					 "vous devez maintenant redémarrer"
					 " le programme pour que celui ci "
					 "soit en français");
	}
	file.close();
}

void FenPrincipale::englishTranslate()
{
	this->checkFrench->setChecked(false);
	this->checkEnglish->setChecked(true);

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
			QMessageBox::critical(this, tr("erreur fichier"),
					      tr("le fichier language n'a pas"
						 " pu s'ouvrir en ecriture"));

		QTextStream out(&file);
		out << "en";
		QMessageBox::information(this, "language",
					 "you must now restart the program to "
					 "have it in english");
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
		this->checkFrench->setChecked(false);
		this->checkEnglish->setChecked(true);
	}

	else
	{
		this->checkFrench->setChecked(true);
		this->checkEnglish->setChecked(false);
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

	if (notFound == "fileNotFound") {
		status_bar->showMessage(
                        tr("fichier language introuvable,"
                           " la langue par defaut a été"
                           " généré"),
                        3500
                );
		if (file.open(QIODevice::WriteOnly| QIODevice::Text)) {
			QTextStream out(&file);
			out << "fr";
		}
		file.close();
	}
}
