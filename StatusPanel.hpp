#ifndef RSA_STATUSPANEL_H
#define RSA_STATUSPANEL_H

#include <QWidget>
#include <QStatusBar>
#include <QLabel>


namespace RSA {

class StatusPanel : public QWidget {
    Q_OBJECT
public:
    StatusPanel(QStatusBar *stbar, QString startEvent, QString endEvent);
    
protected:
    QStatusBar *_statusBar;
    QString _startEvent;
    QString _endEvent;
    
signals:
    void EventStarted();
    void EventEnded();

protected slots:
    void AddStatus();
    void RemoveStatus();
};

}; // end namespace RSA

#endif // RSA_STATUSPANEL_H
