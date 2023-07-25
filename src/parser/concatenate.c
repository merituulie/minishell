/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:26:44 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/25 14:09:54 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../libft/libft.h"

static void	delete_quotes2(char *str, int index, int size, t_data *ms)
{
	int	i;

	i = -1;
	index = 0;
	while (++i < size)
	{
		if (((index + i) == ms->start || (index + i) == ms->end) \
								&& ms->start != ms->end - 1)
			index++;
		else if ((index + i) == ms->start && ms->start == ms->end - 1)
			index = index + 2;
		ms->out[i] = str[index + i];
	}
	ms->out[i] = '\0';
}

/*reallocate the string and delete the first matching quotes*/
void	delete_quotes(char *str, int index, int size, t_data *ms)
{
	char	quote;

	quote = str[index];
	ms->start = index;
	while (str[++index])
	{
		if (str[index] == quote)
		{
			size = size - 2;
			break ;
		}
	}
	ms->end = index;
	ms->out = ft_calloc(size, sizeof(char));
	if (!ms->out)
		printf("allocation error");
	delete_quotes2(str, index, size, ms);
}

/*check if the str has quotes, then find the other matching quote,
delete the quote and returns the string and changes index to where the
last quote deletion happened*/
char	**concatenate(char **str, t_data *ms)
{
	int	i;
	int	j;

	i = -1;
	quotes_init(ms);
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 34 || str[i][j] == 39)
			{
				delete_quotes(str[i], j, ft_strlen(str[i]), ms);
				free(str[i]);
				str[i] = ft_strdup(ms->out);
				if (!str[i])
					printf("strdup error!\n");
				free(ms->out);
				j = ms->end - 2;
			}
		}
	}
	return (str);
}
