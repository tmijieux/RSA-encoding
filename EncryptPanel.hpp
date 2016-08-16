#ifndef RSA_ENCRYPTPANEL_H
#define RSA_ENCRYPTPANEL_H

#include "CryptPanel.hpp"

namespace RSA {

class EncryptPanel : public CryptPanel {
    Q_OBJECT
public:
    EncryptPanel(QStatusBar *sb);

public slots:
    void encrypt();
};


}; // end namespace RSA

#endif // RSA_ENCRYPTPANEL_H
