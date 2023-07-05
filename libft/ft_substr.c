/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:15:53 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/05 09:00:29 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

// char *ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	unsigned int	i;
// 	unsigned int	j;
// 	char			*substr;

// 	i = start;
// 	j = 0;
// 	substr = malloc(sizeof(char) * len + 1);
// 	if (!substr)
// 		return (NULL);
// 	if (!start && !s)
// 		return (0);
// 	if (start > (unsigned int)ft_strlen(s))
// 		len = 0;
// 	while (len > 0 && s[i] != '\0')
// 	{
// 		substr[j] = s[i];
// 		i++;
// 		j++;
// 		len--;
// 	}
// 	substr[j] = '\0';
// 	return (substr);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		len = 0;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && len > 0)
	{
		sub[i] = s[start + i];
		i++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
}
