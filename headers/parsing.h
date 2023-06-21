
#ifndef PARSING_H
# define PARSING_H

# include <stdio.h> //printf, perror
# include <stdlib.h> //malloc, free, exit, getenv
# include <unistd.h> //access, fork, wait, isatty, ttyname, getcwd, execve
# include <sys/wait.h> //waitpid, wait3, wait 4
# include <fcntl.h>
# include <signal.h> //signal,sigaction, sigemptyset, sigaddset
# include <sys/stat.h> // lstat, fstat, stat,
# include <sys/ioctl.h> //ioctl
# include <dirent.h> // opendir, readdir, closedir
# include <termios.h> //tcsetattr, tcgetattr
# include <curses.h>
# include <term.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_data
{
	char	**env;
	char	**args;

}	t_data;

int		main(int argc, char **argv, char **envp);
char	**expand_quote_check(t_data ms, char **str);
char	*expand_var(t_data ms, char *str, int start);

#endif
