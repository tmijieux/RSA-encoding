#ifndef RSA_KEYGENPANEL_H
#define RSA_KEYGENPANEL_H

#include "StatusPanel.hpp"
#include <QWidget>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

namespace RSA {

class KeyGenPanel : public StatusPanel
{
    Q_OBJECT
    private:
    QTextEdit *_textN;
    QTextEdit *_textE;
    QTextEdit *_textD;
    QPushButton *_button;

public:
    KeyGenPanel(QStatusBar *statusBar);
                                       
public slots:
    void GenerateKey();
};

}; // end namespace RSA

#endif // RSA_KEYGENPANEL_H
