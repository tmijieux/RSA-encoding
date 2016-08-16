#include "RSAEncoder.hpp"
#include "EncryptPanel.hpp"

using RSA::EncryptPanel;
using std::string;

EncryptPanel::EncryptPanel(QStatusBar *sb):
    CryptPanel(
        sb,
        tr("Cryptage en cours ..."),
        tr("Le message a été crypté"),
        tr("Entrez la clé N :"),
        tr("Entrez la clé E :"),
        tr("Entrez le message à crypter :"),
        tr("Voici le message décrypté :"),
        tr("Crypter")
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
        QMessageBox::warning( this, tr("erreur"),
                              tr("Un probleme est survenu. "
                                 "Vérifiez la clé et que vous avez entré "
                                 "un texte à crypter !"));
    }
    emit StatusPanel::EventEnded();
}
