#include <sys/file.h>
#include <fcntl.h>
#include "exec-lock.h"
#include <stdio.h>

static const char * fname = "/run/app";

int exec_lock_check()
{
    int fd;

    fd = open(fname, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
        return 0;
    }else{
        return 1;
    }
}
