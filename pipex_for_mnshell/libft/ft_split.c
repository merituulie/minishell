/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:20:31 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/07 14:59:36 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count_word;

	count_word = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count_word++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (count_word);
}

static char	**ft_freeall(char **out)
{
	int	i;

	i = 0;
	while (out[i])
	{
		free(out[i++]);
	}
	free(out);
	return (NULL);
}

static void	ft_putintostr(char **str, char const *s, char c)
{
	char const	*tmp;

	tmp = s;
	while (*tmp)
	{
		while (*s == c)
			s++;
		tmp = s;
		while (*tmp && *tmp != c)
			tmp++;
		if (*tmp == c || tmp > s)
		{
			*str = ft_substr(s, 0, tmp - s);
			if (!str || !*str)
			{
				ft_freeall(str);
				return ;
			}
			s = tmp;
			str++;
		}
	}
	*str = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		count_word;

	if (!s)
		return (NULL);
	count_word = ft_count_words(s, c);
	out = (char **)malloc(sizeof(char *) * (count_word + 1));
	if (!out)
		return (NULL);
	ft_putintostr(out, s, c);
	return (out);
}
