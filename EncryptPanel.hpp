#ifndef ENCRYPTPANEL_H
#define ENCRYPTPANEL_H

#include "CryptPanel.hpp"

class EncryptPanel : public CryptPanel
{
    Q_OBJECT
public:
    EncryptPanel(QStatusBar *sb);

public slots:
    void encrypt();
};

#endif //ENCRYPTPANEL_H
