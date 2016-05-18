#include "KeyGenPanel.hpp"
#include <QLabel>
#include <QGridLayout>

#include "RSAGenerator.hpp"

KeyGenPanel::KeyGenPanel(QStatusBar *status_bar):
    StatusPanel(status_bar,
                "Génération des clés en cours...",
                "Les clés ont été générées")
{
    qbutton = new QPushButton(tr("Générer les clés"), this);
    qbutton->setFont(QFont("Comic Sans MS", 14));

    connect(qbutton, SIGNAL(  clicked()      ),
            this,    SLOT  (  generate_key() ));

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(qbutton, 0, 1, 1, 2);

    layout->addWidget(new QLabel(tr("Voici la cle N : "), this), 1, 0);
    layout->addWidget(new QLabel(tr("Voici la cle D : "), this), 2, 0);
    layout->addWidget(new QLabel(tr("Voici la cle E : "), this), 3, 0);

    NkeyText = new QTextEdit(this);
    NkeyText->setReadOnly(true);

    DkeyText = new QTextEdit(this);
    DkeyText->setReadOnly(true);

    EkeyText = new QTextEdit(this);
    EkeyText->setReadOnly(true);

    layout->addWidget(NkeyText, 1, 1, 2, 2);
    layout->addWidget(DkeyText, 2, 1, 2, 2);
    layout->addWidget(EkeyText, 3, 1, 2, 2);

    this->setLayout(layout);
}

static QString mpz_to_string(mpz_class &c)
{
    size_t length = mpz_sizeinbase(c.get_mpz_t(), 10) + 2;
    char *c_str = new char[length];
    mpz_get_str(c_str, 10, c.get_mpz_t());
    QString s = QString::fromUtf8(c_str, strlen(c_str));

    delete [] c_str;
    return s;
}

void KeyGenPanel::generate_key()
{
    emit event_start();
    try {
        pair<mpz_class, mpz_class> pubkey, private_key;
        RSAGenerator rgen(2048);

        pubkey = rgen.get_public_key();
        private_key = rgen.get_private_key();

        NkeyText->setPlainText(mpz_to_string(pubkey.first));
        EkeyText->setPlainText(mpz_to_string(pubkey.second));
        DkeyText->setPlainText(mpz_to_string(private_key.second));

    } catch (const char *str) {
        puts(str);
    }

    emit event_end();
}
