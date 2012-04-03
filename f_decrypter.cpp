using namespace std;

void FenPrincipale::f_decrypter()
{
	string message_crypte_entre = message_crypte->toPlainText().toStdString();

	int espace = 0;
	decrypt_mot = 1;
	unsigned int i = 0;
	QString message_final;


	try
	{
		mpz_class d(cle_d->text().toStdString()), message_claire, message_crypte_caract, n(cle_n2->text().toStdString());

		if (d == 0 && n ==0)
		{
			n = 8051;
			d = 4783;
		}

		while ( message_crypte_entre[i] != '\0' )
		{
			if ( message_crypte_entre[i] == ' ')
			decrypt_mot++;
			i++;
		}

		message_decrypte->clear();


		for ( i=0; i < decrypt_mot ; i++)
		{
			espace = message_crypte_entre.find(" ");

			message_crypte_caract = message_crypte_entre.substr(0, espace);
			message_crypte_entre.erase(0, (espace + 1));

			mpz_powm (message_claire.get_mpz_t(), message_crypte_caract.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t() );

			message_final = message_claire.get_d();
			message_decrypte->insertPlainText(message_final);
			emit decrypt100();
	 	}
	}

	catch(...)
	{
		QMessageBox::warning(this, tr("erreur"), tr("un probleme vient de se produire il se peut que ce soit: \n \t - vos clés qui sont incorrectes \n \t - votre message crypté qui comporte une erreur (verifier  s'il y a un espace avant le premier nombre ou apres le dernier, si oui: l'enlever)"));
	}

	emit finDecrypt();
}

void FenPrincipale::decrypter_show()
{
	decrypt_bloc = 0;
	decrypt_msg = new QLabel(tr("décryptage en cours"));
	decrypt_msg->setAlignment(Qt::AlignLeft);

	decrypt_lcd = new QProgressBar(this);
	decrypt_lcd->setMaximumHeight(15);
	decrypt_lcd->setGeometry(200, 0, 150, 18);
	decrypt_lcd->setValue(0);

	barreEtat->addWidget(decrypt_msg);
	barreEtat->addWidget(decrypt_lcd);

	connect(this, SIGNAL(finDecrypt()), this, SLOT(rmEtatDecrypt()));
}

void FenPrincipale::decrypt_nb()
{
	decrypt_bloc ++;
	int pourCent;
	pourCent = (decrypt_bloc * 100) / decrypt_mot;
	decrypt_lcd->setValue(pourCent);
}

void FenPrincipale::rmEtatDecrypt()
{
	barreEtat->removeWidget(decrypt_msg);
	barreEtat->removeWidget(decrypt_lcd);
	barreEtat->showMessage(tr("Le message a été décrypté"), 3500);
}

