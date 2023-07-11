/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <vvu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/11 15:38:58 by vvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../headers/env.h"
# include "../libft/libft.h"

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

int	handle_commands(t_command *commands[], t_env **env);

#endif
