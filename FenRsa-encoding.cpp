#include "FenRsa-encoding.hpp"
#include "f_crypter.cpp"
#include "f_decrypter.cpp"
#include "f_cle.cpp"

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
	page3 = new QWidget;

	//Partie crypter
	crypter = new QPushButton(tr("Crypter"), this);
	crypter->setFont(QFont("Comic Sans MS", 14));
	connect(crypter, SIGNAL(released()), this,SLOT(crypter_show()));
	connect(crypter, SIGNAL(clicked()), this , SLOT(f_crypter()));
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
	//decrypter->move(110, 100);

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

	//Partie generateur de cles
	cle = new QPushButton(tr("generer les cles"), this);
	cle->setFont(QFont("Comic Sans MS", 14));
	
	connect(cle, SIGNAL(clicked()), this , SLOT(f_cle()));
	connect(cle, SIGNAL(released()), this,SLOT(creat_cle_show()));

	affiche_cleN = new QTextEdit(this);
	affiche_cleE = new QTextEdit(this);
	affiche_cleD = new QTextEdit(this);
	affiche_cleN->setReadOnly(true);
	affiche_cleE->setReadOnly(true);
	affiche_cleD->setReadOnly(true);

	cleN = new QLabel(tr("Voici la cle N : "), this);
	cleE = new QLabel(tr("Voici la cle E : "), this);
	cleD = new QLabel(tr("Voici la cle D : "), this);

	gbox3 = new  QGridLayout;
	gbox3->addWidget(cle, 0, 1, 1, 2);
	gbox3->addWidget(cleN, 1, 0);
	gbox3->addWidget(cleE, 2, 0);
	gbox3->addWidget(cleD, 3, 0);
	gbox3->addWidget(affiche_cleN, 1, 1, 2, 2);
	gbox3->addWidget(affiche_cleE, 2, 1, 2, 2);
	gbox3->addWidget(affiche_cleD, 3, 1, 2, 2);
	
	
	//Partie Generale assemblage
	page1->setLayout(gbox1);
	page2->setLayout(gbox2);
	page3->setLayout(gbox3);

	onglets->addTab(page1, tr("crypter"));
	onglets->addTab(page2, tr("décrypter"));
	onglets->addTab(page3, tr("cle"));

	setCentralWidget(zoneCentrale);
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

