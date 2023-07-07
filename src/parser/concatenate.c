/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:26:44 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/07 13:06:29 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../libft/libft.h"

/*reallocate the string and delete the first matching quotes*/
void	delete_quotes(char *str, int index, int size, t_data *ms)
{
	char	quote;
	int		i;

	i = -1;
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
	index = 0;
	while (++i < size)
	{
		if ((index + i) == ms->start || (index + i) == ms->end)
			index++;
		ms->out[i] = str[index + i];
	}
	ms->out[i] = '\0';
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
				free(ms->out);
				j = ms->end - 2;
			}
		}
	}
	return (str);
}
