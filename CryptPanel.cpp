#include "CryptPanel.hpp"

using RSA::CryptPanel;

CryptPanel::CryptPanel(QStatusBar *sb, QString event_start, QString event_end,
                       QString key1, QString key2, QString msg1, QString msg2,
                       QString button):
    StatusPanel(sb, event_start, event_end)
{
    _button = new QPushButton(button, this);
    _button->setFont(QFont("Comic Sans MS", 14));

    _key1Line = new QLineEdit(this);
    _key2Line = new QLineEdit(this);
    _msg1Text = new QTextEdit(this);
    _msg2Text = new QTextEdit(this);
    _msg2Text->setReadOnly(true);

    _key1Label = new QLabel(key1);
    _key2Label = new QLabel(key2);
    _msg1Label = new QLabel(msg1);
    _msg2Label = new QLabel(msg2);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(_key1Label, 0, 0);
    layout->addWidget(_key1Line, 0, 1, 1, 2);
    layout->addWidget(_key2Label, 1, 0);
    layout->addWidget(_key2Line, 1, 1, 1, 2);

    layout->addWidget(_msg1Label, 2, 0);
    layout->addWidget(_msg1Text, 2, 1, 1, 2);
    layout->addWidget(_msg2Label, 3, 0);
    layout->addWidget(_msg2Text, 3, 1, 1, 2);

    layout->addWidget(_button, 4, 1, 1, 2);

    this->setLayout(layout);
}
