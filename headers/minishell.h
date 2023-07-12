/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <vvu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/12 16:09:39 by vvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include "hashmap.h"
# include "env.h"
# include <readline/readline.h>
# include <readline/history.h>
/*command is command it self, ex)"echo"
flag is ex) "n"
input is ex) "hello my name"
full_cmd is ex) "echo -n hello my name"*/
typedef struct s_command
{
	char	*command;
	char	*flags;
	char	*input;
	char	*full_cmd;
	char	*infile_name;
	char	*outfile_name;
	int		file_descriptors;
	int		pid;
}	t_command;

int			handle_commands(t_command *commands[], t_env **env);
t_command	*init_cmds(t_command *cmd, char **input);

#endif
