#include "RSAMainWindow.hpp"

using RSA::Window;

void Window::SetupMenu()
{
    _menuBar = menuBar();
    //MENU
    QMenu *fileMenu = _menuBar->addMenu(_("&Fichier"));
    QAction *quitAction = fileMenu->addAction(_("&Quitter"));

    connect(quitAction, SIGNAL (  triggered()  ),
            qApp,        SLOT   (  quit()       ));
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    quitAction->setStatusTip(_("Quitte le programme"));

    // LANGAGE
    QMenu *langMenu = fileMenu->addMenu(_("&Langues"));
    _checkEnglish = langMenu->addAction("english");
    _checkEnglish->setCheckable(true);
    connect(_checkEnglish, SIGNAL ( triggered()        ),
            this,         SLOT   ( TranslateToEnglish() ) );
    _checkEnglish->setStatusTip(_("traduit le logiciel en anglais"));

    _checkFrench = langMenu->addAction("français");
    _checkFrench->setCheckable(true);
    connect(_checkFrench,  SIGNAL (  triggered()       ),
            this,         SLOT   (  TranslateToFrench() ));
    _checkFrench->setStatusTip(_("le logiciel est en francais"));
    CheckLang();
    // FIN LANGAGE

    // AIDE
    QMenu *helpMenu = _menuBar->addMenu(_("&Aide"));
    QAction *help = helpMenu->addAction(_("Aide"));
    help->setShortcut(QKeySequence("F1"));
    connect(help, SIGNAL(  triggered() ),
            this, SLOT  (  DisplayHelp()   ) );
    help->setStatusTip(_("aide du logiciel"));

    // APROPOS
    QAction *aproposSoft = helpMenu->addAction(_("À propos"));
    connect(aproposSoft, SIGNAL(  triggered()   ),
            this,        SLOT  (  DisplayApropos() ));
    aproposSoft->setStatusTip(_("à propos du logiciel"));

    QAction *aproposQT = helpMenu->addAction(_("À propos de Qt"));
    connect(aproposQT, SIGNAL(  triggered() ),
            qApp,      SLOT  (  aboutQt()   ));
    aproposQT->setStatusTip(_("à propos de Qt"));

    // QMenu *menuAffichage = menuBar()->addMenu("&Affichage");
    // FIN AIDE
}

Window::Window()
{
    setWindowTitle("RSA-encoding");

    SetupMenu();
    _statusBar = statusBar();
    CheckLangFile();

    _keyGenPanel = new KeyGenPanel(_statusBar);
    _encryptPanel = new EncryptPanel(_statusBar);
    _decryptPanel = new DecryptPanel(_statusBar);

    _centralWidget = new QWidget();
    _centralWidget->setFixedSize(540, 560);

    QTabWidget *tabs = new QTabWidget(_centralWidget);

    tabs->addTab(_encryptPanel,  _("crypter"));
    tabs->addTab(_decryptPanel, _("décrypter"));
    tabs->addTab(_keyGenPanel, _("clé"));

    setCentralWidget(_centralWidget);
}

void Window::DisplayApropos()
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
    QMessageBox::information(this, _("À propos"), _(msg));
}

void Window::DisplayHelp()
{
    const char *msg;
    msg = "<p>Pour utiliser ce logiciel il vous suffit de rentrer la "
        "clé publique (e, n) et le message secret à transmettre "
        "pour crypter un message et de rentrer la clé privée (d, n) "
        "et le message crypté pour le décrypter ! </p> <p>Si vous "
        "n'avez pas de clé, vous pouvez faire des tests en "
        "utilisant comme clé public (0, 0) et comme clé prive "
        "(0, 0). Ces clés seront automatiquement remplacé par "
        "des clés valides.</p> <p>Bonne utilisation !</p>"
        "<p>N'utilisez pas ce logiciel pour des communications réelles. "
        "Il n'a aucune garantie sur le fonctionnement du logiciel et/ou "
        "la correction des algorithmes</p>";
    QMessageBox::information(this, _("Aide"), _(msg));
}

void Window::TranslateToFrench()
{
    _checkEnglish->setChecked(false);
    _checkFrench->setChecked(true);

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
                this, _("erreur fichier"),
                _("le fichier language n'a pas pu s'ouvrir en écriture"));
        }
        QTextStream out(&file);
        out << "fr";
        QMessageBox::information(
            this, "langue", "vous devez maintenant redémarrer le programme "
            "pour que celui ci soit en français");
    }
    file.close();
}

void Window::TranslateToEnglish()
{
    _checkFrench->setChecked(false);
    _checkEnglish->setChecked(true);

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
                this, _("erreur fichier"),
                _("le fichier language n'a pas pu s'ouvrir en écriture")
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

void Window::CheckLang()
{
    QString language;
    QFile file("language");
    if (file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        language = in.readAll();
        file.close();
    }

    if (language == "en") {
        _checkFrench->setChecked(false);
        _checkEnglish->setChecked(true);
    } else {
        _checkFrench->setChecked(true);
        _checkEnglish->setChecked(false);
    }
}

void Window::CheckLangFile()
{
    QString notFound;
    QFile file("language");

    if (file.open(QFile::ReadOnly)) {
        QTextStream in(&file);
        notFound = in.readAll();
        file.close();
    }

    if (notFound == "fileNotFound") {
        _statusBar->showMessage(
            _("fichier language introuvable,"
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
