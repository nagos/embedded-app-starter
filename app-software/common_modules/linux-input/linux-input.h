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
    enum {KBD_UP, KBD_DOWN, KBD_REPEAT};
    explicit LinuxInput(QString fname);

private slots:
    void slot_get_kbd();

private:
    int event_switches_file_handle;
    QSocketNotifier *sn;

protected:
    virtual void key_event(input_event dat){};
};

#endif // LINUX_INPUT
