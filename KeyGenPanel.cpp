#include "KeyGenPanel.hpp"
#include <QLabel>
#include <QGridLayout>

KeyGenPanel::KeyGenPanel(QMainWindow *window)
{
    QGridLayout *box = new QGridLayout();
        
    //Partie generateur de cles
    keygen_pbutton = new QPushButton(tr("générer les clés"), window);
    keygen_pbutton->setFont(QFont("Comic Sans MS", 14));
    connect(keygen_pbutton, SIGNAL(  clicked() ),
            window,         SLOT  (  f_cle()   )
    );
    connect(keygen_pbutton, SIGNAL(  clicked()           ),
            window,         SLOT  (  add_keygen_status() )
    );
    
    box->addWidget(keygen_pbutton, 0, 1, 1, 2);

    box->addWidget(new QLabel(tr("Voici la cle N : "), window), 1, 0);
    box->addWidget(new QLabel(tr("Voici la cle D : "), window), 2, 0);
    box->addWidget(new QLabel(tr("Voici la cle E : "), window), 3, 0);
        
    NkeyText = new QTextEdit(window);
    NkeyText->setReadOnly(true);
    
    DkeyText = new QTextEdit(window);
    DkeyText->setReadOnly(true);

    EkeyText = new QTextEdit(window);
    EkeyText->setReadOnly(true);
    
    box->addWidget(NkeyText, 1, 1, 2, 2);
    box->addWidget(DkeyText, 2, 1, 2, 2);
    box->addWidget(EkeyText, 3, 1, 2, 2);

    this->setLayout(box);
}

void KeyGenPanel::setNText(const QString &text)
{
    NkeyText->setText(text);
}

void KeyGenPanel::setDText(const QString &text)
{
    DkeyText->setText(text);
}

void KeyGenPanel::setEText(const QString &text)
{
    EkeyText->setText(text);
}
