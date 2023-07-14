/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:07:48 by yoonslee          #+#    #+#             */
/*   Updated: 2023/03/02 16:23:58 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	out = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!out)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			out[i] = s1[i];
	while (s2[j] != '\0')
		out[i++] = s2[j++];
	out[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (out);
}
