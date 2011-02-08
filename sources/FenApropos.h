#ifndef DEF_APROPOS
#define DEF_APROPOS

#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextBrowser>

class FenApropos : public QDialog
{
    public:
    FenApropos(QWidget *parent);
    
    private:
    QTextBrowser *aproposText;
    QPushButton *quit;
    QVBoxLayout *vbox;
};


#endif
