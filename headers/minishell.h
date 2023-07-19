/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/19 10:33:27 by emeinert         ###   ########.fr       */
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

/* If input is 'echo -n "Hello, my name if"' then
command -> "echo"
flags -> "n"
input -> "hello my name"
full_cmd -> "echo -n "Hello, my name if"" */
typedef struct s_command
{
	char	*command;
	char	*flags;
	char	*input;
	char	**full_cmd;
	char	*infile_name;
	char	*outfile_name;
	int		pipe_fds[2];
	int		infile_fd;
	int		outfile_fd;
	int		pid;
	int		id;
}	t_command;

typedef struct s_env
{
	struct s_node	**vars;
}	t_env;

// INITIALIZING
void		fill_env(char **envp, t_env **env);
t_command	*init_cmds(char **input);
int			count_struct(char **input, int struct_count);
char		*ft_strchr_null(const char *s, int c);
void		strdup_if_not_null(t_command *cmd, int track, \
	char *name, char *str);

// IMPLEMENTED COMMANDS
char		*ft_echo(t_command *command, int isPiped);
void		ft_env(t_env **env, t_command *next);
int			ft_execve(t_command *command, t_env **env);

// COMMAND HANDLER
int			execute_commands(t_command *commands, int command_count, t_env **env);
void		execute_command(t_command *command, t_command *next, t_env **env);

// PIPING
int			handle_pipe(t_command *commands, t_env **env);
void		wait_children(int *pids, int count);

// COMMON
void		open_files(t_command **current);
void		close_files(int *pipe_fds, t_command *current);

// TO STRINGS
char	*env_to_string(t_env **env);

#endif
