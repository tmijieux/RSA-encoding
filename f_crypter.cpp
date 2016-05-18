using namespace std;

#define N_DEFAULT 8051
#define E_DEFAULT 79

void FenPrincipale::f_crypter()
{
    std::string message_initial;
    message_initial = this->message_a_crypter->toPlainText().toStdString();
    try {
        mpz_class message_crypte1;
        mpz_class e(cle_e->text().toStdString());
        mpz_class n(cle_n->text().toStdString());
        mpz_class message_clair;

        if (e == 0 && n == 0) {
            n = N_DEFAULT;
            e = E_DEFAULT;
        }

        this->message_crypter->clear();
        this->encrypt_mot = message_initial.size();

        for (unsigned i = 0; i < this->encrypt_mot; ++i) {
            message_clair = message_initial[i];

            // coeur du cryptage:
            mpz_powm(
                message_crypte1.get_mpz_t(),
                message_clair.get_mpz_t(),
                e.get_mpz_t(),
                n.get_mpz_t()
            );
			
            message_crypter->insertPlainText(message_crypte1.get_str().data());
            if (i < this->encrypt_mot - 1)
                this->message_crypter->insertPlainText(" ");
        }
    } catch (...) {
        QMessageBox::warning(
            this, tr("erreur"),
            tr("Un probleme est survenu. "
               "Vérifiez la clé et que vous avez entré "
               "un texte à crypter !")
        );
    }
    emit encrypt_end();
}

void FenPrincipale::add_encrypt_status()
{
    encrypt_status_label = new QLabel(tr("cryptage en cours"));
    encrypt_status_label->setAlignment(Qt::AlignLeft);
    status_bar->addWidget(encrypt_status_label);

    connect(this, SIGNAL(  encrypt_end()   ),
            this, SLOT  (  remove_encrypt_status() )
    );
}

void FenPrincipale::remove_encrypt_status()
{
    status_bar->removeWidget(encrypt_status_label);
    status_bar->showMessage(tr("Le message a été crypté"), 3500);
}
