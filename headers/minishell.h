/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/20 11:23:24 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include "env.h"
# include "parsing.h"
# include "lexer.h"

typedef struct s_command
{
	char	*command;
	char	*flags;
	char	*input;
	char	**full_cmd;
	char	*infile_name;
	char	*outfile_name;
	int		file_descriptors;
	int		pid;
}	t_command;

typedef struct s_data	t_data;

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

char		*ft_echo(t_command *command, int isPiped);

// int	handle_commands(t_command *commands, t_env **env);

#endif
