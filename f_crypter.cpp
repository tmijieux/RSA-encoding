using namespace std;

void FenPrincipale::f_crypter()
{
	string message_initial = message_a_crypter->toPlainText().toStdString();
	unsigned int i = 0;

	try
	{
		mpz_class message_crypte1, e(cle_e->text().toStdString()), n(cle_n->text().toStdString()), message_claire;

		if (e == 0 && n ==0)
		{
			n = 8051;
			e = 79;
		}

		message_crypter->clear();

		encrypt_mot = message_initial.size();

		for (i=0; i < encrypt_mot; i++)
		{
			message_claire =  message_initial[i];
			mpz_powm (message_crypte1.get_mpz_t() , message_claire.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t() );
			message_crypter->insertPlainText(message_crypte1.get_str().data());

			if (i < encrypt_mot - 1)
			message_crypter->insertPlainText(" ");

			emit encrypt100();
		}
	}

	catch(...)
	{
		QMessageBox::warning(this, tr("erreur"), tr("Un probleme est survenue, vérifiez la clé et que vous avez entrez un texte à crypter !"));
	}

	emit finEncrypt();
}

void FenPrincipale::crypter_show()
{
	encrypt_bloc = 0;
	encrypt_msg = new QLabel(tr("cryptage en cours"));
	encrypt_msg->setAlignment(Qt::AlignLeft);

	encrypt_lcd = new QProgressBar(this);
	encrypt_lcd->setMaximumHeight(15);
	encrypt_lcd->setGeometry(200, 0, 150, 18);
	encrypt_lcd->setValue(0);

	barreEtat->addWidget(encrypt_msg);
	barreEtat->addWidget(encrypt_lcd);

	connect(this, SIGNAL(finEncrypt()), this, SLOT(rmEtatEncrypt()));
}

void FenPrincipale::encrypt_nb()
{
	encrypt_bloc ++;
	int pourCent;
	pourCent = (encrypt_bloc * 100) / encrypt_mot;
	encrypt_lcd->setValue(pourCent);
}

void FenPrincipale::rmEtatEncrypt()
{
	barreEtat->removeWidget(encrypt_msg);
	barreEtat->removeWidget(encrypt_lcd);
	barreEtat->showMessage(tr("Le message a été crypté"), 3500);
}
