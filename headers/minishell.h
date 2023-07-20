/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/20 16:15:56 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
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

typedef struct s_data	t_data;

// INITIALIZING
void		fill_env(char **envp, t_env **env);
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
char		*ft_echo(t_command *command, int isPiped);
void		ft_env(t_env **env);
int			ft_execve(t_command *command, t_env **env);

// COMMAND HANDLER
int			execute_commands(t_command *commands, int command_count, t_env **env);
void		execute_command(t_command *command, t_env **env);

// PIPING
int			handle_pipe(t_command *commands, t_env **env, int command_count, int *pipe_fds);
void		wait_children(int *pids, int count);

// COMMON
void		close_files(int *pipe_fds, int command_count);

// TO STRINGS
char	*env_to_string(t_env **env);

#endif
