/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:28 by yoonslee          #+#    #+#             */
/*   Updated: 2022/11/10 14:23:29 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setstart(char const*s1, char const *set)
{
	int	len;
	int	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	ft_setend(char const*s1, char const *set)
{
	int	len;
	int	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[len]) == 0)
			break ;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*out;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = ft_setstart(s1, set);
	end = ft_setend(s1, set);
	out = ft_substr(s1, start, end - start + 1);
	return (out);
}
