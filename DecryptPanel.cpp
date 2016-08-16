#include "RSADecoder.hpp"
#include "DecryptPanel.hpp"

using RSA::DecryptPanel;
#define _(x) tr((x))

DecryptPanel::DecryptPanel(QStatusBar *sb):
    CryptPanel(
        sb,
        _("Décryptage en cours ..."),
        _("Le message a été décrypté"),
        _("Entrez la clé N :"),
        _("Entrez la clé D :"),
        _("Entrez le message à décrypter :"),
        _("Voici le message en clair :"),
        _("Décrypter")
    )
{
    connect(_button, SIGNAL(  clicked() ),
            this,    SLOT  (  Decrypt() ));
}

void DecryptPanel::Decrypt()
{
    emit StatusPanel::EventStarted();
    try {
        mpz_class N(_key1Line->text().toStdString());
        mpz_class D(_key2Line->text().toStdString());

        RSADecoder decoder(N, D);
        string input = _msg1Text->toPlainText().toStdString();
        string output = decoder.decrypt(input);
        _msg2Text->setPlainText(QString::fromUtf8(output.data(),
                                                  output.size()));
    } catch (...) {
        QMessageBox::warning(
            this, _("Erreur"),
            _("un problème vient de se produire il se "
              "peut que ce soit:\n\t - vos clés qui "
              "sont incorrectes\n\t - votre message "
              "crypté qui comporte une erreur (vérifier "
              "s'il y a un espace avant le premier "
              "nombre ou aprés le dernier, si oui: l'enlever).")
        );
    }
    emit StatusPanel::EventEnded();
}
