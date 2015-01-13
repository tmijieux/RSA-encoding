#include "FenRsa-encoding.hpp"
#include "f_crypter.cpp"
#include "f_decrypter.cpp"
#include "f_cle.cpp"

FenPrincipale::FenPrincipale()
{
	setWindowTitle("RSA-encoding");

	//MENU
	this->menuFichier = new QMenu;
	this->menuFichier = menuBar()->addMenu(tr("&Fichier"));
	this->actionQuitter = new QAction(this);
	this->actionQuitter = menuFichier->addAction(tr("&Quitter"));
	connect(this->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
	this->actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

	this->menuLang = new QMenu;
	this->menuLang = this->menuFichier->addMenu(tr("&Langues"));

	this->checkEnglish = new QAction(this);
	this->checkEnglish = menuLang->addAction("english");
	this->checkEnglish->setCheckable(true);
	connect(this->checkEnglish, SIGNAL(triggered()),
		this, SLOT(englishTranslate()));

	this->checkFrench = new QAction(this);
	this->checkFrench = menuLang->addAction("francais");
	this->checkFrench->setCheckable(true);
	connect(this->checkFrench, SIGNAL(triggered()),
		this, SLOT(frenchTranslate()));
	checkLang();

	QMenu *menuAide = menuBar()->addMenu(tr("&Aide"));
	QAction *aide = menuAide->addAction(tr("aide"));
	connect(aide, SIGNAL(triggered()),
		this, SLOT(aideFen()));
	aide->setShortcut(QKeySequence("F1"));
	QAction *aproposSoft = menuAide->addAction(tr("Apropos"));
	connect(aproposSoft, SIGNAL(triggered()),
		this, SLOT(aproposSoftware()));
	QAction *aproposQT = menuAide->addAction(tr("Apropos Qt"));
	connect(aproposQT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	//QMenu *menuAffichage = menuBar()->addMenu("&Affichage");

	//BAR_ETAT
	this->barreEtat = statusBar();
	fileNotFound();
	this->actionQuitter->setStatusTip(tr("Quitte le programme"));
	aproposSoft->setStatusTip(tr("apropos du logiciel"));
	aproposQT->setStatusTip(tr("apropos de Qt"));
	aide->setStatusTip(tr("aide du logiciel"));
	this->checkEnglish->setStatusTip(tr("traduit le logiciel en anglais"));
	this->checkFrench->setStatusTip(tr("le logiciel est en francais"));

	//ZONECENTRALE
	this->zoneCentrale = new QWidget;
	this->zoneCentrale->setFixedSize(540, 560);
	this->onglets = new QTabWidget(zoneCentrale);

	this->page1 = new QWidget;
	this->page2 = new QWidget;
	this->page3 = new QWidget;

	//Partie crypter
	this->crypter = new QPushButton(tr("Crypter"), this);
	this->crypter->setFont(QFont("Comic Sans MS", 14));
	connect(this->crypter, SIGNAL(released()), this,
		SLOT(crypter_show()));
	connect(this->crypter, SIGNAL(clicked()), this,
		SLOT(f_crypter()));
	connect(this, SIGNAL(encrypt100()), this, SLOT(encrypt_nb()));

	this->cle_e = new QLineEdit(this);
	this->cle_n = new QLineEdit(this);
	this->message_a_crypter = new QTextEdit(this);
	this->message_crypter = new QTextEdit(this);
	this->message_crypter->setReadOnly(true);

	this->enter_cle_e = new QLabel(tr("entrez la clé e : "), this);
	this->enter_cle_n = new QLabel(tr("entrez la clé n : "), this);
	this->enter_text = new QLabel(tr("entrez le message"
					 " à crypter : "), this);
	this->text_crypte = new QLabel(tr("voici le message crypté : "), this);

	this->gbox1 = new  QGridLayout;
	this->gbox1->addWidget(this->enter_cle_e, 0, 0);
	this->gbox1->addWidget(this->cle_e, 0, 1, 1, 2);
	this->gbox1->addWidget(this->enter_cle_n, 1, 0);
	this->gbox1->addWidget(this->cle_n, 1, 1, 1, 2);
	this->gbox1->addWidget(this->enter_text, 2, 0);
	this->gbox1->addWidget(this->message_a_crypter, 2, 1, 1, 2);
	this->gbox1->addWidget(this->text_crypte, 3, 0);
	this->gbox1->addWidget(this->message_crypter, 3, 1, 1, 2);
	this->gbox1->addWidget(this->crypter, 4, 1, 1, 2);
	
	//Partie decrypter
	this->decrypter = new QPushButton(tr("Décrypter"), this);
	this->decrypter->setFont(QFont("Comic Sans MS", 14));
	//decrypter->move(110, 100);

	connect(this->decrypter, SIGNAL(clicked()), this,
		SLOT(f_decrypter()));
	connect(this->decrypter, SIGNAL(released()), this,
		SLOT(decrypter_show()));
	connect(this, SIGNAL(decrypt100()), this,
		SLOT(decrypt_nb()));


	this->cle_d = new QLineEdit(this);
	this->cle_n2 = new QLineEdit(this);
	this->message_crypte = new QTextEdit(this);
	this->message_decrypte = new QTextEdit(this);
	this->message_decrypte->setReadOnly(true);

	this->enter_cle_d = new QLabel(tr("entrez la clé d : "), this);
	this->enter_cle_n = new QLabel(tr("entrez la clé n : "), this);
	this->enter_text = new QLabel(tr("entrez le message crypté : "), this);
	this->text_crypte = new QLabel(tr("voici le message decrypté : "), this);

	this->gbox2 = new  QGridLayout;
	this->gbox2->addWidget(this->enter_cle_d, 0, 0);
	this->gbox2->addWidget(this->cle_d, 0, 1, 1, 2);
	this->gbox2->addWidget(this->enter_cle_n, 1, 0);
	this->gbox2->addWidget(this->cle_n2, 1, 1, 1, 2);
	this->gbox2->addWidget(this->enter_text, 2, 0);
	this->gbox2->addWidget(this->message_crypte, 2, 1, 1, 2);
	this->gbox2->addWidget(this->text_crypte, 3, 0);
	this->gbox2->addWidget(this->message_decrypte, 3, 1, 1, 2);
	this->gbox2->addWidget(this->decrypter, 4, 1, 1, 2);

	//Partie generateur de cles
	this->cle = new QPushButton(tr("generer les cles"), this);
	this->cle->setFont(QFont("Comic Sans MS", 14));
	
	connect(this->cle, SIGNAL(clicked()), this, SLOT(f_cle()));
	connect(this->cle, SIGNAL(released()), this,
		SLOT(creat_cle_show()));

	this->affiche_cleN = new QTextEdit(this);
	this->affiche_cleE = new QTextEdit(this);
	this->affiche_cleD = new QTextEdit(this);
	this->affiche_cleN->setReadOnly(true);
	this->affiche_cleE->setReadOnly(true);
	this->affiche_cleD->setReadOnly(true);

	this->cleN = new QLabel(tr("Voici la cle N : "), this);
	this->cleE = new QLabel(tr("Voici la cle E : "), this);
	this->cleD = new QLabel(tr("Voici la cle D : "), this);

	this->gbox3 = new  QGridLayout;
	this->gbox3->addWidget(this->cle, 0, 1, 1, 2);
	this->gbox3->addWidget(this->cleN, 1, 0);
	this->gbox3->addWidget(this->cleE, 2, 0);
	this->gbox3->addWidget(this->cleD, 3, 0);
	this->gbox3->addWidget(this->affiche_cleN, 1, 1, 2, 2);
	this->gbox3->addWidget(this->affiche_cleE, 2, 1, 2, 2);
	this->gbox3->addWidget(this->affiche_cleD, 3, 1, 2, 2);
	
	
	//Partie Generale assemblage
	this->page1->setLayout(this->gbox1);
	this->page2->setLayout(this->gbox2);
	this->page3->setLayout(this->gbox3);

	this->onglets->addTab(this->page1, tr("crypter"));
	this->onglets->addTab(this->page2, tr("décrypter"));
	this->onglets->addTab(this->page3, tr("cle"));

	setCentralWidget(this->zoneCentrale);
}

void FenPrincipale::aproposSoftware()
{
	QMessageBox::information(this, tr("Apropos"),
				 tr(
     "<p>Ce programme fut réalisé par Alexandre GAY avec le soutien "
     "d'Armand Comparot, de Thomas Mijieux et de Robin PHILIBERT.</p>"
     " <p>Les codes sources sont libre et gratuit, vous pouvez les retrouver"
     " sur le site à l'addresse <a href='http://protecinfo.redheberg.com'>"
     "protecinfo.redheberg</a> .</p> <p>Vous trouverez sur le site une page "
     "forum ou vous pourez donner votre avis sur le logiciel.</p> <p>Pour plus "
     "d'information n'hésitez pas à nous contacter sur le site ou par mail</p>"
     " <p>Merci d'utiliser notre logiciel.</p>"));
}

void FenPrincipale::aideFen()
{
	QMessageBox::information(this,tr("Aide"), tr(
    "<p>Pour utiliser ce logiciel il vous suffit de rentrer les clés public"
    " (e, n) et le message secret à transmetre pour crypter un message et de"
    " rentrer les clés privé (d, n) et le message crypté pour le décrypter !"
    "</p> <p>Si vous n'avez pas de clé, vous pouvez faire des tests en "
    "utilisant comme clé public (0, 0) et comme clé prive (0, 0). Ces clé "
    "seront automatiquement remplacé par des clés valides.</p> <p>Bonne "
    "utilisation !</p>"));
}

void FenPrincipale::frenchTranslate()
{
	this->checkEnglish->setChecked(false);
	this->checkFrench->setChecked(true);

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

	if (notFound == "fileNotFound")
	{
		this->barreEtat->showMessage(tr("fichier language introuvable,"
					  " la langue par defaut a été généré"),
				       3500);
		if (file.open(QIODevice::WriteOnly| QIODevice::Text))
		{
			QTextStream out(&file);
			out << "fr";
		}
		file.close();
	}
}
