#include "RSAMainWindow.hpp"

void RSAMainWindow::setup_menu()
{
    menu_bar = menuBar();
    //MENU
    QMenu *file_menu = menu_bar->addMenu(tr("&Fichier"));
    QAction *action_quit = file_menu->addAction(tr("&Quitter"));

    connect(action_quit, SIGNAL (  triggered()  ),
            qApp,        SLOT   (  quit()       ));
    action_quit->setShortcut(QKeySequence("Ctrl+Q"));
    action_quit->setStatusTip(tr("Quitte le programme"));

    // LANGAGE
    QMenu *lang_menu = file_menu->addMenu(tr("&Langues"));
    checkEnglish = lang_menu->addAction("english");
    checkEnglish->setCheckable(true);
    connect(checkEnglish, SIGNAL ( triggered()        ),
            this,         SLOT   ( english_translate() ) );
    checkEnglish->setStatusTip(tr("traduit le logiciel en anglais"));

    checkFrench = lang_menu->addAction("français");
    checkFrench->setCheckable(true);
    connect(checkFrench,  SIGNAL (  triggered()       ),
            this,         SLOT   (  french_translate() ));
    checkFrench->setStatusTip(tr("le logiciel est en francais"));
    this->check_lang();
    // FIN LANGAGE

    // AIDE
    QMenu *help_menu = menu_bar->addMenu(tr("&Aide"));
    QAction *help = help_menu->addAction(tr("Aide"));
    help->setShortcut(QKeySequence("F1"));
    connect(help, SIGNAL(  triggered() ),
            this, SLOT  (  help_message()   ) );
   help->setStatusTip(tr("aide du logiciel"));
   
    // APROPOS
    QAction *aproposSoft = help_menu->addAction(tr("À propos"));
    connect(aproposSoft, SIGNAL(  triggered()       ),
            this,        SLOT  (  apropos_software() ));
    aproposSoft->setStatusTip(tr("à propos du logiciel"));
    
    QAction *aproposQT = help_menu->addAction(tr("À propos de Qt"));
    connect(aproposQT, SIGNAL(  triggered() ),
            qApp,      SLOT  (  aboutQt()   ));
    aproposQT->setStatusTip(tr("à propos de Qt"));
    
    // QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    // FIN AIDE
}

RSAMainWindow::RSAMainWindow()
{
    setWindowTitle("RSA-encoding");
 
    setup_menu();
    status_bar = statusBar();
    this->file_not_found();
        
    keyGenPanel = new KeyGenPanel(status_bar);
    encryptPanel = new EncryptPanel(status_bar);
    decryptPanel = new DecryptPanel(status_bar);
    
    central_widget = new QWidget();
    central_widget->setFixedSize(540, 560);

    QTabWidget *tabs = new QTabWidget(central_widget);
    
    tabs->addTab(encryptPanel,  tr("crypter"));
    tabs->addTab(decryptPanel, tr("décrypter"));
    tabs->addTab(keyGenPanel, tr("clé"));

    setCentralWidget(central_widget);
}

void RSAMainWindow::apropos_software()
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
    QMessageBox::information(this, tr("À propos"), tr(msg));
}

void RSAMainWindow::help_message()
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
    QMessageBox::information(this, tr("Aide"), tr(msg));
}

void RSAMainWindow::french_translate()
{
    checkEnglish->setChecked(false);
    checkFrench->setChecked(true);

    QString language;
    QFile file("language");
    if (file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        language = in.readAll();
        file.close();
    }

    if (language != "fr") {
        if (!file.open(QIODevice::WriteOnly| QIODevice::Text)) {
            QMessageBox::critical(
                this, tr("erreur fichier"),
                tr("le fichier language n'a pas pu s'ouvrir en écriture"));
        }
        QTextStream out(&file);
        out << "fr";
        QMessageBox::information(
            this, "langue", "vous devez maintenant redémarrer le programme "
            "pour que celui ci soit en français");
    }
    file.close();
}

void RSAMainWindow::english_translate()
{
    checkFrench->setChecked(false);
    checkEnglish->setChecked(true);

    QString language;
    QFile file("language");
    if (file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        language = in.readAll();
        file.close();
    }

    if (language != "en") {
        if (!file.open(QIODevice::WriteOnly| QIODevice::Text)) {
            QMessageBox::critical(
                this, tr("erreur fichier"),
                tr("le fichier language n'a pas pu s'ouvrir en écriture")
            );
        }

        QTextStream out(&file);
        out << "en";
        QMessageBox::information(
            this, "language",
            "you must now restart the program to have it in english"
        );
    }
    file.close();
}

void RSAMainWindow::check_lang()
{
    QString language;
    QFile file("language");
    if (file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        language = in.readAll();
        file.close();
    }

    if (language == "en") {
        checkFrench->setChecked(false);
        checkEnglish->setChecked(true);
    } else {
        checkFrench->setChecked(true);
        checkEnglish->setChecked(false);
    }
}

void RSAMainWindow::file_not_found()
{
    QString notFound;
    QFile file("language");
    if (file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        notFound = in.readAll();
        file.close();
    }
    
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
