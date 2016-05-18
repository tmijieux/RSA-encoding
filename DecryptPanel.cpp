#include "RSADecoder.hpp"
#include "DecryptPanel.hpp"

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
    connect(qbutton, SIGNAL(  clicked() ),
            this,    SLOT  (  decrypt() ));
}

void DecryptPanel::decrypt()
{
    emit event_start();
    try {
        mpz_class N(key1_line->text().toStdString());
        mpz_class D(key2_line->text().toStdString());

        RSADecoder decoder(N, D);
        string input = msg1_text->toPlainText().toStdString();
        string output = decoder.decrypt(input);
        msg2_text->setPlainText(QString::fromUtf8(output.data(), output.size()));

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

    emit event_end();
}

