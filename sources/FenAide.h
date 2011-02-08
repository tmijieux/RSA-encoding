#ifndef DEF_AIDE
#define DEF_AIDE

#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>

class FenAide : public QDialog
{
    public:
    FenAide(QWidget *parent);
    
    private:
    QTextEdit *aideText;
    QPushButton *quit;
    QVBoxLayout *vbox;
};


#endif
