/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:31:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/19 14:01:12 by emeinert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../headers/hashmap.h"
#include "../../libft/libft.h"

char	*ft_strchr_null(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

/*here it <<, >> case should be added.*/
int	count_struct(char **input, int struct_count)
{
	int	index;

	index = 0;
	while (input[index])
	{
		if ((ft_strchr_null("<|>", input[index][0])) || index == 0)
		{
			struct_count++;
			index++;
		}
		else
			index++;
	}
	return (struct_count);
}

void	parse_input(t_command *cmd, int track, char *str)
{
	if (!str)
		return ;
	
	cmd[track].input = ft_strdup(str);
	if (!cmd[track].input)
		printf("strdup allocation fail!\n");
}

void	parse_flags(t_command *cmd, int track, char *str)
{
	if (!str)
		return ;
	cmd[track].flags = ft_strdup(str);
	if (!cmd[track].flags)
		printf("strdup allocation fail!\n");
}
