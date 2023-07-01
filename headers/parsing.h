
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
# include "../libft/libft.h"

// typedef struct s_node
// {
// 	char			*key;
// 	char			*value;
// 	struct s_node	*next;
// }	t_node;

typedef struct s_data
{
	char	**env;
	char	**args;
	int		start;
	int		end;
	int		s_quotes;
	int		d_quotes;
	char	*out;

}	t_data;

int		main(int argc, char **argv, char **envp);

/*expand_env.c*/
char	**expand_quote_check(t_data *ms, char **str);
void	expand_var(t_data *ms, char *str, int start);
void	realloc_var(t_data *ms, char *str, char *var, int start);
char	*find_env(t_data *ms, char *var, int var_size);

/*libft_files.c -- delete later*/
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
int		ft_isalnum(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void	*dst, const void *src, size_t n);


#endif
