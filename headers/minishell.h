/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/27 13:21:45 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <errno.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "lexer.h"
# include "hashmap.h"

typedef struct s_command
{
	char	*command;
	char	*flags;
	char	*input;
	char	**full_cmd;
	char	*infile_name;
	char	*outfile_name;
	int		*fds;
	int		pid;
	int		id;
}	t_command;

typedef struct s_env
{
	struct s_node	**vars;
}	t_env;

typedef struct s_info
{
	int	exit_code;
}	t_info;

typedef struct s_data	t_data;

t_info		g_info;

// INITIALIZING
void		fill_env(char **envp, t_env **env);

/*init_command.c*/
t_command	*init_cmds(t_data *ms, char **input);
int			count_struct(char **input, int struct_count);
/*add_command.c*/
char		*put_to_input(char **input, int *index);
char		*put_to_flags(char **input, int	*index);
char		*put_to_file(char **input, int **index);
void		put_redirection(t_command *cmd, int *index, \
			int track, char **input);
void		put_cmd_to_struct(t_command *cmd, int index, \
					int struct_count, char **input);
/*utils_command.c*/
char		*ft_strchr_null(const char *s, int c);
void		strdup_if_not_null(t_command *cmd, int track, \
			char *name, char *str);
void		strdup_filename(t_command *cmd, int track, char *str);
void		put_fullcmd(t_command *cmd, int i, int track);
void		full_cmd(t_command *cmd, int struct_count, int track);

// IMPLEMENTED COMMANDS
int			ft_echo(t_command *command);
void		ft_env(t_env **env);
void		ft_cd(t_command *command, t_env **env);
int			ft_heredoc(t_command *command);
int			ft_execve(t_command *command, t_env **env);
int			ft_pwd(t_env *env);
void		ft_exit(t_command *command);

// COMMAND HANDLER
int			execute_commands(t_command *commands, int command_count, \
					t_env **env);
void		execute_command(t_command *command, t_env **env);

// PIPING
int			handle_pipe(t_command *commands, t_env **env, int command_count, \
				int *pipe_fds);
void		wait_children(int *pids, int count);

// COMMON
void		close_files(int *pipe_fds, int command_count);
void		error_code(int number);
void		error_msg(char *str, t_command *command);

// TO STRINGS
char		*env_to_string(t_env **env);

// COMMANDS

void		ft_export(char *cmd, t_env *env);
void		ft_unset(char *cmd, t_env *env);

#endif
