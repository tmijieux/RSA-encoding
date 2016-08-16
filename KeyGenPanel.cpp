#include "KeyGenPanel.hpp"
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>

#include "RSAGenerator.hpp"

using std::pair;
using RSA::KeyGenPanel;

#define _(x) tr((x))

KeyGenPanel::KeyGenPanel(QStatusBar *statusBar):
    StatusPanel(statusBar,
                _("Génération des clés en cours..."),
                _("Les clés ont été générées"))
{
    _button = new QPushButton(_("Générer les clés"), this);
    _button->setFont(QFont("Comic Sans MS", 14));

    connect(_button, SIGNAL( clicked()     ),
            this,    SLOT  ( GenerateKey() ));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(_button, 0, 1, 1, 2);

    _textN = new QTextEdit(this);
    _textN->setReadOnly(true);

    _textD = new QTextEdit(this);
    _textD->setReadOnly(true);

    _textE = new QTextEdit(this);
    _textE->setReadOnly(true);

    layout->addWidget(new QLabel(_("Voici la clé N : "), this), 1, 0);
    layout->addWidget(_textN, 1, 1, 2, 2);
    layout->addWidget(new QLabel(_("Voici la clé D : "), this), 2, 0);
    layout->addWidget(_textD, 2, 1, 2, 2);
    layout->addWidget(new QLabel(_("Voici la clé E : "), this), 3, 0);
    layout->addWidget(_textE, 3, 1, 2, 2);

    this->setLayout(layout);
}

static QString MpzToString(mpz_class &c)
{
    size_t length = mpz_sizeinbase(c.get_mpz_t(), 10) + 2;
    char *c_str = new char[length];
    mpz_get_str(c_str, 10, c.get_mpz_t());
    QString s = QString::fromUtf8(c_str, strlen(c_str));

    delete [] c_str;
    return s;
}

void KeyGenPanel::GenerateKey()
{
    emit StatusPanel::EventStarted();
    try {
        pair<mpz_class, mpz_class> pubkey, privateKey;
        Generator rgen(1024);

        pubkey = rgen.GetPublicKey();
        privateKey = rgen.GetPrivateKey();

        _textN->setPlainText(MpzToString(pubkey.first));
        _textE->setPlainText(MpzToString(pubkey.second));
        _textD->setPlainText(MpzToString(privateKey.second));

    } catch (const char *str) {
        puts(str);
    } catch ( ... ) {
        QMessageBox::warning(
            this, _("erreur"),
            _("Un problème est survenue pendant la génération des clés")
        );
    }
    emit StatusPanel::EventEnded();
}
