#ifndef RSA_DECRYPTPANEL_H
#define RSA_DECRYPTPANEL_H

#include "CryptPanel.hpp"

namespace RSA {
class DecryptPanel : public CryptPanel {
    Q_OBJECT
public:
    DecryptPanel(QStatusBar *sb);

public slots:
    void Decrypt();
};


}; // end namespace RSA

#endif // RSA_DECRYPTPANEL_H
