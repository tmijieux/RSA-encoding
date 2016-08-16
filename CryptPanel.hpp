#ifndef RSA_CRYPTPANEL_H
#define RSA_CRYPTPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QTranslator>
#include <QMessageBox>
#include <QGridLayout>

#include "StatusPanel.hpp"

namespace RSA {

class CryptPanel : public StatusPanel {
protected:
    QLabel *_key1Label;
    QLabel *_key2Label;
    QLabel *_msg1Label;
    QLabel *_msg2Label;

    QLineEdit *_key1Line;
    QLineEdit *_key2Line;

    QTextEdit *_msg1Text;
    QTextEdit *_msg2Text;

    QPushButton *_button;

public:
    CryptPanel(QStatusBar *sb,
               QString eventStart, QString eventEnd,
               QString key1, QString key2,
               QString msg1, QString msg2,
               QString button);
    virtual ~CryptPanel() {}
};


}; // end namespace rsa

#endif // RSA_CRYPTPANEL_H
