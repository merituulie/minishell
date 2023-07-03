/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/03 13:08:13 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>

typedef struct s_command
{
	char	*command;
	char	*command_flags;
	char	*infile_name;
	char	*outfile_name;
	int		file_descriptors;
	int		pid;
}	t_command;

// int handle_commands(t_command **commands, t_env **env);

#endif
