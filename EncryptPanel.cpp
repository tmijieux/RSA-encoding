#include "RSAEncoder.hpp"
#include "EncryptPanel.hpp"

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
    connect(qbutton, SIGNAL(  clicked() ),
            this,    SLOT  (  encrypt() ));
}

void EncryptPanel::encrypt()
{
    emit event_start();
    try {
        mpz_class N(key1_line->text().toStdString());
        mpz_class E(key2_line->text().toStdString());

        RSAEncoder encoder(N, E);
        string input = msg1_text->toPlainText().toStdString();
        string output = encoder.encrypt(input);
        msg2_text->setPlainText(QString::fromUtf8(output.data(), output.size()));

    } catch (...) {
        QMessageBox::warning( this, tr("erreur"),
                              tr("Un probleme est survenu. "
                                 "Vérifiez la clé et que vous avez entré "
                                 "un texte à crypter !"));
    }
    emit event_end();
}
