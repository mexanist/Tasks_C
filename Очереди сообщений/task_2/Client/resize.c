#include <ncurses.h>
#include <signal.h>
#include <sys/ioctl.h>

void sig_winch(int signo){
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}

