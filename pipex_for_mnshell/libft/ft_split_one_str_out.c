/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_one_str_out.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:59:54 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/07 15:20:05 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words_one_str_out(char const *s, char c)
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

static char	*ft_freeall_one_str_out(char *out)
{
	int	i;

	i = 0;
	free(out);
	out = NULL;
	return (NULL);
}

static void	ft_putintostr_one_str_out(char *str, char const *s, char c)
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
			str = ft_substr(s, 0, tmp - s);
			if (!str || !*str)
			{
				ft_freeall_one_str_out(str);
				return ;
			}
			s = tmp;
			str++;
		}
	}
	str = NULL;
}

char	*ft_split_one_str_out(char const *s, char c)
{
	char	*out;
	int		count_word;

	if (!s)
		return (NULL);
	count_word = ft_count_words_one_str_out(s, c);
	out = (char *)malloc(sizeof(char *) * (count_word + 1));
	if (!out)
		return (NULL);
	ft_putintostr_one_str_out(out, s, c);
	return (out);
}
