/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:42:15 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/25 06:21:20 by jhusso           ###   ########.fr       */
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
}
