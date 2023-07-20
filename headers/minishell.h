/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/07/20 11:45:50 by rmakinen         ###   ########.fr       */
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
	int		file_descriptors;
	int		pid;
}	t_command;

typedef struct s_data	t_data;

t_command	*init_cmds(t_data *ms, char **input);
int			count_struct(char **input, int struct_count);
char		*ft_strchr_null(const char *s, int c);
void		strdup_if_not_null(t_command *cmd, int track, \
	char *name, char *str);

int		handle_commands(t_command *commands, t_env **env);

int			ft_pwd(t_env **env);
int			ft_echo(t_command *command);

#endif
