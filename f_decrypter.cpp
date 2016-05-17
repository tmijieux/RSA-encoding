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

		for (unsigned int i = 0; message_crypte_entre[i] != '\0'; ++i) {
			if (message_crypte_entre[i] == ' ')
				this->decrypt_mot ++;
		}

		this->message_decrypte->clear();

		for (unsigned i = 0; i < this->decrypt_mot ; i++) {
			int espace = message_crypte_entre.find(" ");
                        
			message_crypte_caract = message_crypte_entre
                                .substr(0, espace);
			message_crypte_entre.erase(0, (espace + 1));

			// décryptage:
			mpz_powm(message_claire.get_mpz_t(),
				 message_crypte_caract.get_mpz_t(),
				 d.get_mpz_t(),
				 n.get_mpz_t() );
			
			message_final = message_claire.get_d();
			this->message_decrypte->insertPlainText(message_final);
			emit decrypt_100();
	 	}
	} catch (...) {
		QMessageBox::warning(this, tr("erreur"),
				     tr("un probleme vient de se produire il se"
					" peut que ce soit: \n \t - vos clés qui"
					" sont incorrectes \n \t - votre message"
					" crypté qui comporte une erreur (verifier"
					"  s'il y a un espace avant le premier"
					" nombre ou apres le dernier, si oui:"
					" l'enlever)"));
	}

	emit decrypt_end();
}

void FenPrincipale::decrypter_show()
{
	this->decrypt_bloc = 0;
	this->decrypt_msg = new QLabel(tr("décryptage en cours"));
	this->decrypt_msg->setAlignment(Qt::AlignLeft);

	this->decrypt_lcd = new QProgressBar(this);
	this->decrypt_lcd->setMaximumHeight(15);
	this->decrypt_lcd->setGeometry(200, 0, 150, 18);
	this->decrypt_lcd->setValue(0);

	this->barreEtat->addWidget(this->decrypt_msg);
	this->barreEtat->addWidget(this->decrypt_lcd);

	connect(this, SIGNAL(finDecrypt()), this,
		SLOT(rmEtatDecrypt()));
}

void FenPrincipale::decrypt_nb()
{
	this->decrypt_bloc ++;
	int pourcent = (this->decrypt_bloc * 100) / this->decrypt_mot;
	this->decrypt_lcd->setValue(pourcent);
}

void FenPrincipale::rmEtatDecrypt()
{
	this->barreEtat->removeWidget(this->decrypt_msg);
	this->barreEtat->removeWidget(this->decrypt_lcd);
	this->barreEtat->showMessage(tr("Le message a été décrypté"), 3500);
}

