/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:21:26 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/02 19:07:30 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "parsing.h"
# include "lexer.h"
# include "hashmap.h"
# include <termios.h>

# ifndef HEREDOC
#  define HEREDOC "heredoc.txt"
# endif

enum e_redirect
{
	NONE = 0,
	OUTPUT_TRUNC = 1,
	OUTPUT_APPEND = 2,
	INPUT = 3
};

typedef struct s_command
{
	char	*command;
	char	*flags;
	char	**input;
	char	**full_cmd;
	char	*infile_name;
	char	*outfile_name;
	int		redir_fd_index;
	int		token;
	int		in_heredoc;
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
	int	sig_status;
	int	*pipe_fds;
	int	pipe_count;
	int	*redir_fds;
	int	redir_count;
	int	redir_index_count;
}	t_info;

typedef struct s_data	t_data;

t_info					g_info;

// INITIALIZING
void		fill_env(char **envp, t_env **env);

// COMMAND
t_command	*init_cmds(t_data *ms, char **input);
void		put_to_input(t_command *cmd, int track, char *str, char **not_echo);
void		put_to_flags(t_command **cmd, int track, char *str);
char		*parse_flags(char **input, int	*index);
char		*parse_input(char **input, int *index);
int			parse_redirection(t_command *cmd, int track, char *str, \
			char *input);
void		handle_redirection(t_command *cmd, int *index, int track, \
			char **input);
void		put_cmds_to_struct(t_command *cmd, char **input, t_data *ms);
char		*ft_strchr_null(const char *s, int c);
void		put_fullcmd(t_command *cmd, int i, int track);
void		full_cmd(t_command *cmd, int struct_count, int track);
void		put_fullcmd_input(t_command	*cmd, int i, int track, int index);
char		**copy_input(char **input, int *index);
int			handle_heredoc(t_command *cmd, int *index, int track, char **input);

//EXPORT UNSET UTILS
int			check_unset_export_input(char *input);

// IMPLEMENTED COMMANDS
void		ft_echo(t_command *command);
void		ft_env(t_env **env, t_command *command);
void		ft_cd(t_command *command, t_env **env);
int			ft_heredoc(t_command *command, t_env **env, char *delim);
int			ft_execve(t_command *command, t_env **env);
int			ft_pwd(t_env *env);
void		ft_exit(t_command *command, int fork);
void		ft_export(char **input, t_env *env);
void		ft_unset(char **input, t_env *env);


//	SHLVL
void		add_shlvl(t_env **env);

// COMMAND HANDLER
int			execute_commands(t_command *commands, int command_count, \
					t_env **env);
void		execute_command(t_command *command, t_env **env, int fork);
int			execute_builtin(t_command **command, t_env ***env, int fork);

// PIPING
int			handle_pipe(t_command *commands, t_env **env, int command_count);
void		wait_children(int *pids, int count);

// REDIRECTIONS
void		redirect_io(int infile_fd, int outfile_fd);
void		redirect_files(t_command *current);
void		ft_dup2(int infile_fd, int outfile_fd);

// COMMON
void		close_files(int *pipe_fds, int fd_count);
int			open_file(char *filename, int flags);
int			close_file(int fd);
void		open_redirection_file(t_command *current);
void		error_code(int number);
void		error_msg(int code, char *str, t_command *command);
char		*get_exit_value(void);
int			*allocate_pids(int pid_count);

// TO STRINGS
char		*env_to_string(t_env **env);
void		print_export_env(t_env **env);

// SIGNALS:
void		set_signal_action(t_data *ms);
void		restore_terminal(t_data *ms);
void		ctrl_d_cmd(char *line, t_data *ms);
void		heredoc_signal(int signo);

// FREE
void		free_cmd_struct(t_command *command, int cmd_count);
void		free_in_main(t_data *data);
void		free_in_minishell(t_command *cmd, int cmd_count, char **cmd_line);

#endif
