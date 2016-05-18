using namespace std;

#define N_DEFAULT 8051
#define D_DEFAULT 4783

void FenPrincipale::f_decrypter()
{
    std::string message_crypte_entre;
    message_crypte_entre = this->message_crypte->toPlainText().toStdString();
    this->decrypt_mot = 1;
    QString message_final;
    try {
        mpz_class d(cle_d->text().toStdString());
        mpz_class message_claire, message_crypte_caract;
        mpz_class n(cle_n2->text().toStdString());

        if (d == 0 && n == 0) {
            n = N_DEFAULT;
            d = D_DEFAULT;
        }

        for (unsigned i = 0; message_crypte_entre[i] != '\0'; ++i) {
            if (message_crypte_entre[i] == ' ')
                this->decrypt_mot ++;
        }

        this->message_decrypte->clear();
        for (unsigned i = 0; i < this->decrypt_mot ; i++) {

            int espace = message_crypte_entre.find(" ");
            message_crypte_caract = message_crypte_entre.substr(0, espace);
            message_crypte_entre.erase(0, (espace + 1));

            // décryptage:
            mpz_powm(
                message_claire.get_mpz_t(),
                message_crypte_caract.get_mpz_t(),
                d.get_mpz_t(),
                n.get_mpz_t()
            );
            message_final = message_claire.get_d();
            this->message_decrypte->insertPlainText(message_final);
        }
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

    emit decrypt_end();
}

void FenPrincipale::add_decrypt_status()
{
    decrypt_status_label = new QLabel(tr("décryptage en cours"));
    decrypt_status_label->setAlignment(Qt::AlignLeft);
    status_bar->addWidget(decrypt_status_label);

    connect(this, SIGNAL(  decrypt_end()     ),
            this, SLOT  (  remove_decrypt_status()) );
}

void FenPrincipale::remove_decrypt_status()
{
    status_bar->removeWidget(decrypt_status_label);
    status_bar->showMessage(tr("Le message a été décrypté"), 3500);
}

