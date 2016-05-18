
void FenPrincipale::f_cle()
{
    mpz_class p(0), q(0), e(0), n(0), c(0);
    double graine = time(NULL); // nul !

    while (e == 0) {
        mpz_t rand_Num;
        gmp_randstate_t rstate;
        mpz_init(rand_Num);

        gmp_randinit_default(rstate);
        gmp_randseed_ui(rstate, graine);

        if (q == 0)
            mpz_urandomb(rand_Num, rstate, 200);
        else
            mpz_urandomb(rand_Num, rstate, 50);

        int reps = 50;
        if (mpz_probab_prime_p(rand_Num, reps) != 0 && p == 0) {
            mpz_class tmp(rand_Num);
            p = tmp;
            //cout << "p " << rand_Num << endl;
        } else if (mpz_probab_prime_p(rand_Num, reps) != 0 &&
                   q == 0 && e == 0)	{
            mpz_class tmp(rand_Num);
            q = tmp;
            //cout << "q " << rand_Num << endl;
        } else if (mpz_probab_prime_p(rand_Num, reps) != 0 && q != 0) {
            mpz_class tmp(rand_Num);
            e = tmp;
            //cout << "e " << rand_Num << endl;
        }

        graine ++;
        gmp_randclear(rstate);
        mpz_clear(rand_Num);
    }

    c = (p-1)*(q-1);
    n = p*q;

    //cout << endl << "e : " << e << endl << "n : " << n;
    keyGenPanel.setNText(n.get_str().data());
    keyGenPanel.setEText(e.get_str().data());

    // **recherche de D**
    mpz_class tmp, diviseur, d;
    vector<mpz_class> r, x;
    int i = 0, i2 = 0, alt1 = -1;

    do {
        mpz_t r_tmp;
        mpz_init(r_tmp);

        if (i == 0) {
            mpz_mod(r_tmp, c.get_mpz_t() ,e.get_mpz_t());
            mpz_class r_tmp2(r_tmp);
            r.push_back(r_tmp2);
            diviseur = ((c-r[0])/e);

        } else if (i == 1) {
            mpz_mod(r_tmp, e.get_mpz_t(), r[0].get_mpz_t());
            mpz_class r_tmp2(r_tmp);
            r.push_back(r_tmp2);
            diviseur = ((e-r[1])/r[0]);

        } else {
            mpz_mod(r_tmp, r[i-2].get_mpz_t(), r[i-1].get_mpz_t());
            mpz_class r_tmp2(r_tmp);
            r.push_back(r_tmp2);
            diviseur = ((r[i-2] - r[i]) / r[i-1]);
        }

        tmp = r[i];
        i++;
    } while (tmp > 1);

    for (i = r.size() - 2;  i >= 0; --i) {
        if (i == (signed) r.size() - 2)	{
            tmp = (r[i-2] * diviseur+1) / r[i-1];
            // sans doute prob ici, old: d[i-2]
            x.push_back(tmp);

        } else if (i == 0) {
            tmp = (x[i2-1]*c+alt1)/e;
            x.push_back(tmp);

        } else if (i == 1) {
            tmp = (x[i2-1]*e+alt1)/r[i-1];
            x.push_back(tmp);
            alt1 *= -1;

        } else {
            tmp = (x[i2-1]*r[i-2]+alt1)/r[i-1];
            x.push_back(tmp);
            alt1 *= -1;
        }

        i2++;
    }

    int taille = r.size();
    d = x[taille-2];

    if ((x[taille-3]*c)-(d*e) != 1 && (x[taille-3]*c)-(d*e) != -1) {
        keyGenPanel.setNText("problème : d normalement incorrecte");
    } else {
        if (alt1 == -1)
            d = c - d;
        keyGenPanel.setDText(d.get_str().data());
    }
    emit keygen_end();
}

void FenPrincipale::add_keygen_status()
{
    keygen_status_label = new QLabel(tr("génération des clés en cours..."));
    keygen_status_label->setAlignment(Qt::AlignLeft);
    status_bar->addWidget(keygen_status_label);

    connect(this, SIGNAL(  keygen_end()            ),
            this, SLOT  (  remove_keygen_status()) );
}

void FenPrincipale::remove_keygen_status()
{
    status_bar->removeWidget(keygen_status_label);
    status_bar->showMessage(tr("Les clés ont été généré"), 3500);
}
