/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <vvu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:49:28 by meskelin          #+#    #+#             */
/*   Updated: 2023/07/12 15:51:20vvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
#include "headers/hashmap.h"
#include "headers/env.h"
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


int ft_strcmp(char *s1, char *s2)
{
	unsigned char *str1;
	unsigned char *str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (!str1 || !str2)
		return (*str1 - *str2);
	while (*str1)
	{	
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
 	}
	return (*str1 - *str2);
}

int	main(void)
{
	char		*buf;
	char		**input;
	t_command	*lst_cmd;

	lst_cmd = NULL;
	while (1)
	{
		buf = readline("Rainbow>> ");
		add_history(buf);
		if (ft_strcmp(buf, "exit") == 0)
		{
			free(buf);
			break;
		}
		else
		{
			input = ft_split(buf, ' ');
			lst_cmd = init_cmds(input);
			int i = 0;
			printf("command[1] is %s\n", lst_cmd[1].command);
			while (lst_cmd[i].command)
			{
				printf("In Main: i is %d\n", i);
				printf("Command: %s, address %p\n", lst_cmd[i].command, &lst_cmd[i].command);
				printf("flags: %s, address %p\n", lst_cmd[i].flags, &lst_cmd[i].flags);
				printf("input: %s, address %p\n", lst_cmd[i].input, &lst_cmd[i].input);
				i++;
			}
		}
		free(input);
		free(buf);
	}
	return 0;
}
