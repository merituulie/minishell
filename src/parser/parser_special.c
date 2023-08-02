/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:48:00 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/02 17:27:53 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../libft/libft.h"

char	*special_expand(t_data *ms, char *str)
{
	while (!ft_isalnum(str[ms->end]) && str[ms->end] != ' ' && \
			str[ms->end] != '$' && str[ms->end])
		ms->end++;
	if (!str[ms->end])
	{
		free(str);
		return ("");
	}
	else
	{
		ms->out = ft_substr(str, ms->end, ft_strlen(str) - ms->end);
		if (!ms->out)
			return (NULL);
		free(str);
		ms->end = 0;
		return (ms->out);
	}
}

void	free_case(t_data *ms)
{
	if (ms->out)
		free(ms->out);
}

int	count_size(char *str, char *var, char *new)
{
	int	size;

	if (!new)
		size = ft_strlen(str) - ft_strlen(var);
	else
		size = ft_strlen(str) - ft_strlen(var) + ft_strlen(new);
	return (size);
}

int	only_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\n')
			return (0);
	}
	return (1);
}
