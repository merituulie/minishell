/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:59:19 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 09:59:20 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parsing.h"
# include "lexer.h"
# include "hashmap.h"

# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
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
	int		redir_fd_index_in;
	int		redir_fd_index_out;
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

// BUILTINS
void		ft_cd(t_command *command, t_env **env);
void		ft_echo(t_command *command);
int			execute_ft_execve(t_command *command, t_env **env);
int			ft_execve(t_command *command, t_env **env);
void		ft_exit(t_command *command, t_env *env, int fork, int flag);
void		ft_export(char **input, t_env *env);
char		*expand_var_here(t_data *ms, char *str, int start, t_env **env);
int			ft_heredoc(t_command *command, t_env **env, char *delim);
int			ft_pwd(t_env *env);
void		exp_unset_exit_msg(char *input, int command);
void		ft_unset(char **input, t_env *env);

// COMMAND
void		put_cmds_to_struct(t_command *cmd, char **input, t_data *ms);
void		delete_quotes_struct(t_command *cmd, t_data *ms);
char		*parse_flags(char **input, int	*index);
void		put_to_flags(t_command **cmd, int track, char *str);
void		put_fullcmd_input(t_command	*cmd, int i, int track, int index);
void		put_fullcmd(t_command *cmd, int i, int track);
void		full_cmd(t_command *cmd, int struct_count, int track);
void		update_command_redir(t_command *command);
int			handle_heredoc(t_command *cmd, int *index, int track, char **input);
t_command	*init_cmds(t_data *ms, char **input);
char		*add_input_part(int str_len, int space_count, char **input, \
			int cur_index);
char		*parse_input(char **input, int *index);
char		**copy_input(char **input, int *index, char **not_echo);
void		put_to_input(t_command *cmd, int track, char *str, char **not_echo);
void		update_infile_redir_heredoc(t_command *cmd, int track);
int			check_null_index_handle_redirs(t_command *cmd, int track, \
			char **input, int *index);

// COMMON
void		execute_command(t_command *command, t_env **env, int fork);
void		execute_commands(t_command *commands, int command_count, \
					t_env **env);
int			accessable_for_open(char *filename, int flags);
int			open_file(char *filename, int flags);
void		close_file(int fd);
void		close_files(int *pipe_fds, int fd_count);
int			open_redirection_file(t_command *current);
void		free_cmd_struct(t_command *command, int cmd_count);
void		free_in_main(t_data *data);
void		close_free_fd_arrays(void);
void		free_in_minishell(t_command *cmd, int cmd_count);
int			*allocate_pids(int pid_count);
void		wait_children(int *pids, int count);
int			handle_pipe(t_command *commands, t_env **env, int command_count);
void		ft_dup2(int infile_fd, int outfile_fd);
void		redirect_io(int infile_fd, int outfile_fd);
void		redirect_files(t_command *current);
int			parse_redirection(t_command *cmd, int track, char *str, \
			char *input);
void		clear_failed_redir(t_command *cmd);
void		cmd_is_not_executable(t_command *command);
void		set_exit_code(int number);
char		*get_exit_code(void);
void		ft_puterror(int code, char *str, t_command *command);
void		add_shlvl(t_env **env);
void		ctrl_d_cmd(char *line, t_data *ms);
void		restore_terminal(t_data *ms);
void		adjust_status(int status);
void		set_signal_action(t_data *ms);

// ENV
void		print_export_env(t_env **env);
char		*env_to_string(t_env **env);
void		ft_env(t_env **env, t_command *command);
void		fill_env(char **envp, t_env **env);

#endif
