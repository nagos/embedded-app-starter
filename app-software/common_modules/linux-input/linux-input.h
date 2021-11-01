#if !defined(LINUX_INPUT)
#define LINUX_INPUT

#include <QObject>
#include <QSocketNotifier>

#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

class LinuxInput: public QObject
{
    Q_OBJECT
public:
    LinuxInput(QString fname);

private slots:
    void slot_get_kbd();

private:
    int event_switches_file_handle;
    QSocketNotifier *sn;

protected:
    virtual void key_event(uint16_t type, uint16_t code, uint32_t value){};
};

#endif // LINUX_INPUT
