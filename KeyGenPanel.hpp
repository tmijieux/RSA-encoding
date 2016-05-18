
#include <QWidget>
#include <QTextEdit>
#include <QMainWindow>
#include <QPushButton>

class KeyGenPanel : public QWidget
{
    Q_OBJECT
    
private:
    QTextEdit *NkeyText;
    QTextEdit *EkeyText;
    QTextEdit *DkeyText;
    QPushButton *keygen_pbutton;

public:
    KeyGenPanel(QMainWindow *window);
    void setNText(const QString &text);
    void setDText(const QString &text);
    void setEText(const QString &text);
};
