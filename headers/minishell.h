/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/17 12:48:08 by yoonslee         ###   ########.fr       */
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

int			handle_commands(t_command *commands[], t_env **env);
t_command	*init_cmds(char **input);
char		*ft_echo(t_command *command, int isPiped);

// int	handle_commands(t_command *commands, t_env **env);

#endif
