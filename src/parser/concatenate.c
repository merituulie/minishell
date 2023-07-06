/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:26:44 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/06 15:08:08 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../libft/libft.h"

void	delete_quotes(char *str, int index, int size, t_data *ms)
{
	char	quote;
	int		i;

	i = -1;
	printf("--------------------delete_quotes starts\n");
	quote = str[index];
	ms->start = index;
	printf("quote is %c, ms.start is %d, size is %d\n", quote, ms->start, size);
	while (str[++index])
	{
		if (str[index] == quote)
		{
			size = size - 2;
			break ;
		}
	}
	ms->end = index;
	printf("quote is %c, ms.end is %d, size is %d\n", str[index], ms->end, size);
	printf("ms.out's size is %d\n", size);
	ms->out = ft_calloc(size, sizeof(char));
	printf("ms.out's size is %d\n", size);
	index = 0;
	while (++i < size)
	{
		// printf("i is %d\n", i);
		if ((index + i) == ms->start || (index + i) == ms->end)
			index++;
		ms->out[i] = str[index + i];
		// printf("ms->out[%d] = str[%d]\n", i, (index + i));
		// printf("ms.out[%d] is %c\n", i, ms->out[i]);
	}
	printf("i is %d\n", i);
	ms->out[i] = '\0';
	// printf("ms.out str size is %d\n", (int)ft_strlen(ms->out));
	printf("ms.out str result is %s\n", ms->out);
	printf("--------------------delete_quotes ends\n");
}

char	**concatenate(char **str, t_data *ms)
{
	int	i;
	int	j;

	i = -1;
	quotes_init(ms);
	while (str[++i])
	{
		printf("str[i] is %d\n", i);
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 34 || str[i][j] == 39)
			{
				printf("str[i][%d]\n", j);
				delete_quotes(str[i], j, ft_strlen(str[i]), ms);
				free(str[i]);
				str[i] = ft_strdup(ms->out);
				free(ms->out);
				printf("after delete_quotes, the string is %s\n", str[i]);
				j = ms->end - 2;
				printf("j is %d, string length is %zu\n", j, ft_strlen(str[i]));
			}
		}
		printf("after concatenate, the string is %s\n", str[i]);
	}
	return (str);
}
