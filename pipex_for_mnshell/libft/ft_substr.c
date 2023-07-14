/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:51:14 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/07 10:54:30 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
ft_substr(char const *s, unsigned int start, size_t len)
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*out;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	out = malloc (sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		out[i] = s[start + i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
