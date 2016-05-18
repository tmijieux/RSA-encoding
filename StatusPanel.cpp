#include <StatusPanel.hpp>

StatusPanel::StatusPanel(
    QStatusBar *stbar, QString start_event, QString end_event)
{
    sbar = stbar;
    connect(this, SIGNAL( event_start() ),
            this, SLOT  ( add_status()  ));
    connect(this, SIGNAL( event_end() ),
            this, SLOT  ( remove_status()  ));

    status_label = new QLabel(start_event);
    status_label->setAlignment(Qt::AlignLeft);
    this->end_event = end_event;
}

void StatusPanel::add_status()
{
    sbar->addWidget(status_label);
}

void StatusPanel::remove_status()
{
    sbar->removeWidget(status_label);
    sbar->showMessage(end_event, 3500);
}
