/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 08:43:30 by meskelin          #+#    #+#             */
/*   Updated: 2022/11/14 16:35:57 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *str, const char limit)
{
	const char	*s;
	int			counter;

	s = str;
	counter = 0;
	while (*s)
	{
		if (*s != limit)
			if (s == str || *(s - 1) == limit)
				counter++;
		s++;
	}
	return (counter);
}

static void	ft_add_words(char **new, const char *str, char limit, int index)
{
	const char	*ptr;
	const char	*start;

	ptr = str;
	while (*ptr)
	{
		if (*ptr != limit)
		{
			if (ptr == str || *(ptr - 1) == limit)
			{
				start = ptr;
				while (*ptr && *ptr != limit)
					ptr++;
				if (ft_count_words(ptr, limit) > 0)
					ft_add_words(new, ptr, limit, index + 1);
				new[index] = (char *)malloc(ptr - start + 1);
				if (new[index] != NULL)
					ft_strlcpy(new[index], start, ptr - start + 1);
				return ;
			}
		}
		else
			ptr++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	count;

	if (s == NULL)
		return (NULL);
	count = ft_count_words(s, c);
	split = (char **)malloc(sizeof(char *) * (count + 1));
	if (split == NULL)
		return (NULL);
	split[count] = NULL;
	ft_add_words(split, s, c, 0);
	return (split);
}
