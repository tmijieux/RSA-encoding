#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <QWidget>
#include <QStatusBar>
#include <QLabel>

class StatusPanel : public QWidget {
    Q_OBJECT

public:
    StatusPanel(QStatusBar *stbar, QString start_event, QString end_event);
    
protected:
    QStatusBar *sbar;
    QString start_event;
    QString end_event;
    
signals:
    void event_start();
    void event_end();

protected slots:
    void add_status();
    void remove_status();

};


#endif //STATUSPANEL_H
