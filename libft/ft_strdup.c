/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvu <vvu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:01:01 by vvu               #+#    #+#             */
/*   Updated: 2022/12/20 16:26:51 by vvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*pt;
	int		i;

	i = 0;
	pt = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!pt)
		return (NULL);
	while (*s1)
		pt[i++] = *s1++;
	pt[i] = '\0';
	return (pt);
}
