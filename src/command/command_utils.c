/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:31:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/19 10:16:59 by yoonslee         ###   ########.fr       */
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

void	strdup_if_not_null(t_command *cmd, int track, char *name, char *str)
{
	if (!ft_strncmp_all("flags", name))
	{
		printf("name is %s\n", name);
		if (str == NULL)
			cmd[track].flags = NULL;
		else
		{
			cmd[track].flags = ft_strdup(str);
			if (!cmd[track].flags)
				printf("strdup allocation fail!\n");
		}
	}
	else if (!ft_strncmp_all("input", name))
	{
		printf("name is %s\n", name);
		if (str == NULL)
			cmd[track].input = NULL;
		else
		{
			cmd[track].input = ft_strdup(str);
			if (!cmd[track].input)
				printf("strdup allocation fail!\n");
		}
	}
}
