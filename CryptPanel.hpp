#ifndef CRYPTPANEL_H
#define CRYPTPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTranslator>
#include <QMessageBox>
#include <QGridLayout>

#include "StatusPanel.hpp"

using std::string;

class CryptPanel : public StatusPanel {
protected:
    QLabel *key1_label;
    QLabel *key2_label;
    QLabel *msg1_label;
    QLabel *msg2_label;

    QLineEdit *key1_line;
    QLineEdit *key2_line;

    QTextEdit *msg1_text;
    QTextEdit *msg2_text;

    QPushButton *qbutton;

public:
    CryptPanel(QStatusBar *sb, QString event_start, QString event_end,
               QString key1, QString key2, QString msg1, QString msg2,
               QString button);
    virtual ~CryptPanel() {}
};

#endif //CRYPTPANEL_H
