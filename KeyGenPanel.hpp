#ifndef KEYGENPANEL_H
#define KEYGENPANEL_H

#include "StatusPanel.hpp"
#include <QWidget>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>

class KeyGenPanel : public StatusPanel
{
    Q_OBJECT
    
private:
    QTextEdit *NkeyText;
    QTextEdit *EkeyText;
    QTextEdit *DkeyText;
    QPushButton *qbutton;

public:
    KeyGenPanel(QStatusBar *status_bar);
                                       
public slots:
    void generate_key();
};

#endif //KEYGENPANEL_H
