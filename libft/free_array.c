/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:56:41 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/25 14:57:00 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_char_array(char **str)
{
	int		i;
	char	*input;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		input = str[i];
		free(input);
		i++;
	}
	free(str);
}
