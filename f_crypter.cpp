using namespace std;

#define N_DEFAULT 8051
#define E_DEFAULT 79

void FenPrincipale::f_crypter()
{
	std::string message_initial = this->message_a_crypter->toPlainText()
		                             .toStdString();
	try
	{
		mpz_class message_crypte1;
		mpz_class e(cle_e->text().toStdString());
		mpz_class n(cle_n->text().toStdString());
		mpz_class message_claire;

		if (e == 0 && n == 0)
		{
			n = N_DEFAULT;
			e = E_DEFAULT;
		}

		this->message_crypter->clear();
		this->encrypt_mot = message_initial.size();

		for (unsigned int i = 0; i < this->encrypt_mot; i++)
		{
			message_claire = message_initial[i];

			// coeur du cryptage:
			mpz_powm(message_crypte1.get_mpz_t(),
				 message_claire.get_mpz_t(),
				 e.get_mpz_t(),
				 n.get_mpz_t());
			
			this->message_crypter->insertPlainText(message_crypte1
							 .get_str().data());
			if (i < this->encrypt_mot - 1)
				this->message_crypter->insertPlainText(" ");
			emit this->encrypt100();
		}
	}

	catch (...)
	{
		QMessageBox::warning(this, tr("erreur"),
				     tr("Un probleme est survenue,"
					" vérifiez la clé et que vous avez entrez"
					" un texte à crypter !"));
	}

	emit finEncrypt();
}

void FenPrincipale::crypter_show()
{
	this->encrypt_bloc = 0;
	this->encrypt_msg = new QLabel(tr("cryptage en cours"));
	this->encrypt_msg->setAlignment(Qt::AlignLeft);

	this->encrypt_lcd = new QProgressBar(this);
	this->encrypt_lcd->setMaximumHeight(15);
	this->encrypt_lcd->setGeometry(200, 0, 150, 18);
	this->encrypt_lcd->setValue(0);

	this->barreEtat->addWidget(this->encrypt_msg);
	this->barreEtat->addWidget(this->encrypt_lcd);

	connect(this, SIGNAL(this->finEncrypt()), this,
		SLOT(this->rmEtatEncrypt()));
}

void FenPrincipale::encrypt_nb()
{
	this->encrypt_bloc ++;
	int pourcent = (this->encrypt_bloc * 100) / this->encrypt_mot;
	this->encrypt_lcd->setValue(pourcent);
}

void FenPrincipale::rmEtatEncrypt()
{
	this->barreEtat->removeWidget(this->encrypt_msg);
	this->barreEtat->removeWidget(this->encrypt_lcd);
	this->barreEtat->showMessage(tr("Le message a été crypté"), 3500);
}
