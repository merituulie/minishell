/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:21:30 by yoonslee          #+#    #+#             */
/*   Updated: 2023/06/20 17:12:48 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

/*free double pointer string*/
void	free_char_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

/* 1 is pipe, 2 is < or > or << or >>
error value 258 needs to be returned*/
void	syntax_error_msg(int i, char **str)
{
	if (i == 1)
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
	else
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
	free_char_array(str);
	exit(258);
}

/*check the syntax error: if there is error, send exit message with
proper exit value. can we use exit(258)? I don't know :/ */
int	syntax_error(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '|' || (str[i] == '|' && !str[i + 1]))
			syntax_error_msg(1, str);
		if ((str[i] == '<' || str[i] == '<' || str[i] == '>>' || str[i] == '<<')
			&& !str[i + 1])
			syntax_error_msg(2, str);
		i++;
	}
	return (0);
}
