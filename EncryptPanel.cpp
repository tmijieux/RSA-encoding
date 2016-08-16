#include "RSAEncoder.hpp"
#include "EncryptPanel.hpp"

using RSA::EncryptPanel;
using std::string;
#define _(x) tr((x))

EncryptPanel::EncryptPanel(QStatusBar *sb):
    CryptPanel(
        sb,
        _("Cryptage en cours ..."),
        _("Le message a été crypté"),
        _("Entrez la clé N :"),
        _("Entrez la clé E :"),
        _("Entrez le message à crypter :"),
        _("Voici le message décrypté :"),
        _("Crypter")
    )
{
    connect(_button, SIGNAL(  clicked() ),
            this,    SLOT  (  encrypt() ));
}

void EncryptPanel::encrypt()
{
    emit StatusPanel::EventStarted();
    try {
        mpz_class N(_key1Line->text().toStdString());
        mpz_class E(_key2Line->text().toStdString());

        Encoder encoder(N, E);
        string input = _msg1Text->toPlainText().toStdString();
        string output = encoder.Encrypt(input);
        _msg2Text->setPlainText(QString::fromUtf8(output.data(), output.size()));

    } catch (...) {
        QMessageBox::warning( this, _("Erreur"),
                              _("Un probleme est survenu. "
                                "Vérifiez la clé et que vous avez entré "
                                "un texte à crypter !"));
    }
    emit StatusPanel::EventEnded();
}
