/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:54:35 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/11 08:27:42 by rmakinen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../headers/env.h"
# include "../libft/libft.h"

typedef struct s_command
{
	char	*command;
	char	*command_flags;
	char	*infile_name;
	char	*outfile_name;
	int		file_descriptors;
	int		pid;
}	t_command;

int		handle_commands(t_command *commands[], t_env **env);
char	*ft_echo(t_command *command, int isPiped);

#endif
