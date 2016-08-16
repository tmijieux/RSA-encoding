#include "RSADecoder.hpp"
#include "DecryptPanel.hpp"

using RSA::DecryptPanel;

DecryptPanel::DecryptPanel(QStatusBar *sb):
    CryptPanel(
        sb,
        tr("Décryptage en cours ..."),
        tr("Le message a été décrypté"),
        tr("Entrez la clé N :"),
        tr("Entrez la clé D :"),
        tr("Entrez le message à décrypter :"),
        tr("Voici le message en clair :"),
        tr("Décrypter")
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
            this, tr("erreur"),
            tr("un probleme vient de se produire il se"
               " peut que ce soit: \n \t - vos clés qui"
               " sont incorrectes \n \t - votre message"
               " crypté qui comporte une erreur (vérifier"
               "  s'il y a un espace avant le premier"
               " nombre ou apres le dernier, si oui: l'enlever)")
        );
    }
    emit StatusPanel::EventEnded();
}
