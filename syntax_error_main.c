/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 19:02:22 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/03 19:03:26 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"
#include "libft/libft.h"

int	main(void)
{
	char	**str;

	str = ft_calloc(3, sizeof(char *));
	str[0] = ft_strdup("hello");
	str[1] = ft_strdup("<");
	if (!syntax_error(str))
		printf("no syntax error\n");
	return (0);
}
