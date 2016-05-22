#include <StatusPanel.hpp>

StatusPanel::StatusPanel(
    QStatusBar *stbar, QString start_event, QString end_event)
{
    sbar = stbar;
    connect(this, SIGNAL( event_start() ),
            this, SLOT  ( add_status()  ));
    connect(this, SIGNAL( event_end() ),
            this, SLOT  ( remove_status()  ));

    this->start_event = start_event;
    this->end_event = end_event;
}

void StatusPanel::add_status()
{
    sbar->showMessage(start_event);
}

void StatusPanel::remove_status()
{
    sbar->showMessage(end_event, 3500);
}
