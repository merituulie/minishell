/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:48:00 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/15 17:47:36 by yoonslee         ###   ########.fr       */
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

int	count_size(char *str, char *var, char *new)
{
	int	size;

	if (!new)
		size = ft_strlen(str) - ft_strlen(var);
	else
		size = ft_strlen(str) - ft_strlen(var) + ft_strlen(new);
	return (size);
}

int	space_newline(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	break_in_expand_quote(char *str, t_data *ms)
{
	if (!str)
		return (-1);
	if (ms->out)
	{
		free(ms->out);
		ms->out = NULL;
	}
	if (ms->end - 1 >= (int)ft_strlen(str))
		return (-1);
	return (0);
}

int	find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && !is_delim(str[i + 1]) && str[i + 1] \
		&& str[i + 1] != c)
			return (i);
		i++;
	}
	return (-1);
}
