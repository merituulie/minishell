/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:42:15 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/14 18:46:01 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../libft/libft.h"

/*initialize the quotes count to zero*/
void	quotes_init(t_data *ms)
{
	ms->s_quotes = 0;
	ms->d_quotes = 0;
}

void	free_str_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
	}
	if (str)
		free(str);
}

void	ms_init(t_data *ms)
{
	ms->end = 0;
	ms->start = 0;
	ms->s_quotes = 0;
	ms->d_quotes = 0;
	ms->struct_count = 0;
}

void	realloc_var2(t_data *ms, int leftover, int size, char *str)
{
	ms->k = -1;
	while ((leftover + (++(ms->k))) < size)
		ms->out[leftover + ms->k] = str[ms->end + ms->k];
	ms->out[leftover + ms->k] = '\0';
	ms->end = leftover;
	if (!(ms->out))
		ms->out = NULL;
}

char	*expand_var_init(t_data *ms, char *str, int start)
{
	ms->start = start;
	ms->end = start + 1;
	str = NULL;
	return (str);
}
