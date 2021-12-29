#include "linux-input.h"
#include <QDebug>

LinuxInput::LinuxInput(QString fname)
{
    event_switches_file_handle = open(fname.toLocal8Bit(), O_RDONLY);
    Q_ASSERT(event_switches_file_handle>0);
    sn = new QSocketNotifier(event_switches_file_handle, QSocketNotifier::Read);
    sn->setEnabled(true);
    connect(sn, &QSocketNotifier::activated, this, &LinuxInput::slot_get_kbd);
}

void LinuxInput::slot_get_kbd()
{
    input_event dat;
    int num = read(event_switches_file_handle, &dat, sizeof(input_event));
    Q_UNUSED(num);
    if(dat.type==EV_KEY)
        key_event(dat);
}
