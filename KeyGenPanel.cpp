#include "KeyGenPanel.hpp"
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>

#include "RSAGenerator.hpp"

using std::pair;
using RSA::KeyGenPanel;

KeyGenPanel::KeyGenPanel(QStatusBar *statusBar):
    StatusPanel(statusBar,
                "Génération des clés en cours...",
                "Les clés ont été générées")
{
    _button = new QPushButton(tr("Générer les clés"), this);
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

    layout->addWidget(new QLabel(tr("Voici la cle N : "), this), 1, 0);
    layout->addWidget(_textN, 1, 1, 2, 2);
    layout->addWidget(new QLabel(tr("Voici la cle D : "), this), 2, 0);
    layout->addWidget(_textD, 2, 1, 2, 2);
    layout->addWidget(new QLabel(tr("Voici la cle E : "), this), 3, 0);
    layout->addWidget(_textE, 3, 1, 2, 2);

    this->setLayout(layout);
}

static QString mpz_to_string(mpz_class &c)
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

        _textN->setPlainText(mpz_to_string(pubkey.first));
        _textE->setPlainText(mpz_to_string(pubkey.second));
        _textD->setPlainText(mpz_to_string(privateKey.second));

    } catch (const char *str) {
        puts(str);
    } catch ( ... ) {
        QMessageBox::warning(
            this, tr("erreur"),
            tr("Un problème est survenue pendant la génération des clés\n")
        );
    }
    emit StatusPanel::EventEnded();
}
