/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:25:47 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/06 12:47:52 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "env.h"

typedef struct s_data
{
	struct s_env	*env;
	char			**args;
	int				start;
	int				end;
	int				s_quotes;
	int				d_quotes;
	char			*out;
}	t_data;

int		main(int argc, char **argv, char **envp);

/*expand_env.c*/
char	**expand_quote_check(t_data *ms, char **str);
void	expand_var(t_data *ms, char *str, int start);
void	realloc_var(t_data *ms, char *str, char *var, int start);
char	*find_env(t_data *ms, char *var, int var_size);

/*conctenate.c*/
char	**concatenate(char **str, t_data *ms);

/*utils.c*/
void	quotes_init(t_data *ms);
void	free_str_array(char **str);

#endif
