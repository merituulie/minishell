
#include <stdio.h> //printf, perror
#include <stdlib.h> //malloc, free, exit, getenv
#include <unistd.h> //access, fork, wait, isatty, ttyname, getcwd, execve
#include <sys/wait.h> //waitpid, wait3, wait 4
#include <fcntl.h>
#include <signal.h> //signal,sigaction, sigemptyset, sigaddset
#include <sys/stat.h> // lstat, fstat, stat,
#include <sys/ioctl.h> //ioctl
#include <dirent.h> // opendir, readdir, closedir
#include <termios.h> //tcsetattr, tcgetattr
#include <curses.h>
#include <term.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

