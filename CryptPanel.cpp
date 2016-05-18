#include "CryptPanel.hpp"

CryptPanel::CryptPanel(QStatusBar *sb, QString event_start, QString event_end,
                       QString key1, QString key2, QString msg1, QString msg2,
                       QString button):
    StatusPanel(sb, event_start, event_end)
{
    qbutton = new QPushButton(button, this);
    qbutton->setFont(QFont("Comic Sans MS", 14));

    key1_line = new QLineEdit(this);
    key2_line = new QLineEdit(this);
    msg1_text = new QTextEdit(this);
    msg2_text = new QTextEdit(this);
    msg2_text->setReadOnly(true);

    key1_label = new QLabel(key1);
    key2_label = new QLabel(key2);
    msg1_label = new QLabel(msg1);
    msg2_label = new QLabel(msg2);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(key1_label, 0, 0);
    layout->addWidget(key1_line, 0, 1, 1, 2);
    layout->addWidget(key2_label, 1, 0);
    layout->addWidget(key2_line, 1, 1, 1, 2);

    layout->addWidget(msg1_label, 2, 0);
    layout->addWidget(msg1_text, 2, 1, 1, 2);
    layout->addWidget(msg2_label, 3, 0);
    layout->addWidget(msg2_text, 3, 1, 1, 2);

    layout->addWidget(qbutton, 4, 1, 1, 2);

    this->setLayout(layout);
}
