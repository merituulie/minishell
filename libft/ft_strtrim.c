/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:52:57 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:52:58 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	is_set(char const c, char *set)
{
	int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char *set)
{
	size_t	i;
	size_t	j;
	int		k;
	char	*trim;

	if (s1 == 0)
		return (0);
	i = 0;
	while (s1[i] && is_set(s1[i], set))
		i ++;
	j = ft_strlen(s1);
	while (j > i && is_set(s1[j - 1], set))
		j --;
	trim = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!trim)
		malloc_error();
	k = 0;
	while (i < j)
		trim[k++] = s1[i++];
	trim[k] = '\0';
	return (trim);
}
