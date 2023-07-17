/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:31:26 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/17 15:18:20 by yoonslee         ###   ########.fr       */
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

//here it <<, >> case should be added.
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
