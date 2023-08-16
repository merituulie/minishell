/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:25:47 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/16 14:30:19 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
# include <errno.h>
# include "../libft/libft.h"
# include "minishell.h"

typedef struct s_data
{
	struct s_env		*env;
	struct termios		old_tio;
	struct termios		new_tio;
	struct sigaction	sa;
	char				**args;
	int					start;
	int					end;
	int					s_quotes;
	int					d_quotes;
	char				*out;
	int					i;
	int					j;
	int					k;
	int					struct_count;
}	t_data;

/*expand_env.c*/
char	**expand_quote_check(t_data *ms, char **str);
char	*expand_var(t_data *ms, char *str, int start);
void	realloc_var(t_data *ms, char *str, char *var, int size);
char	*find_env(t_data *ms, char *var, int var_size);

/*conctenate.c*/
char	**concatenate(char **str, t_data *ms);
int		extend_expand_quote_check2(t_data *ms, char **str);

/*utils.c*/
void	quotes_init(t_data *ms);
void	free_str_array(char **str);
void	ms_init(t_data *ms);
void	realloc_var2(t_data *ms, int leftover, int size, char *str);
char	*expand_var_init(t_data *ms, char *str, int start);

/*parser_special.c*/
char	*special_expand(t_data *ms, char *str);
int		count_size(char *str, char *var, char *new);
int		space_newline(char *str);
int		break_in_expand_quote(char *str, t_data *ms);
int		find_index(char *str, char c);

#endif
