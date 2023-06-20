
#ifndef MINISHELL_H
# define MINISHELL_H

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

# define T_NULL 0
# define T_COMMAND 1
# define T_GREATER_THAN 3

# define T_PIPE 4
# define T_DOUBLE_QUOTES 5 
# define T_SINGLE_QUOTES 6
# define T_SPACE 7

// typedef struct s_token{
// 	int		type;
// 	char	*str;
// }	t_token;

// typedef struct s_command{
// 	int		type;
// 	char	*str;
// }	t_command;

typedef struct s_envp{
	char			*data;
	struct s_envp	*next;
}	t_envp;

typedef struct s_data{
	struct t_envp	env;
}	t_data;


int		main(int argc, char **argv, char **envp);
void	expand_quote_check(t_data ms, char **str);
void	expand_var(t_data ms, char *str, int start);


#endif
