#include "StatusPanel.hpp"

using RSA::StatusPanel;

StatusPanel::StatusPanel(
    QStatusBar *statusBar, QString startEvent, QString endEvent):
    _statusBar(statusBar), _startEvent(startEvent), _endEvent(endEvent)
{
    connect(this, SIGNAL( EventStarted() ),
            this, SLOT  ( AddStatus() ));
    connect(this, SIGNAL( EventEnded() ),
            this, SLOT  ( RemoveStatus() ));
}

void StatusPanel::AddStatus()
{
    _statusBar->showMessage(_startEvent);
}

void StatusPanel::RemoveStatus()
{
    _statusBar->showMessage(_endEvent, 3500);
}
