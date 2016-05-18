#ifndef DECRYPTPANEL_H
#define DECRYPTPANEL_H

#include "CryptPanel.hpp"

class DecryptPanel : public CryptPanel {
    Q_OBJECT
public:
    DecryptPanel(QStatusBar *sb);

public slots:
    void decrypt();
};

#endif //DECRYPTPANEL_H
