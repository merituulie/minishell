/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:47:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/05 14:01:45 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/* 1 is pipe, 2 is < or > or << or >>
error value 258 needs to be returned*/
void	syntax_error_msg(int i, char **str)
{
	if (i == 1)
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
	if (i == 2)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
	if (i == 3)
		ft_putstr_fd("syntax error: quotes not ended\n", 2);
	free_char_array(str);
	exit(258);
}

/*if the single quotes or double quotes doesn't have a pair ending*/
void	quote_check(char **str, int i, char quote)
{
	int	j;

	j = 1;
	while (str[i][j])
	{
		if (str[i][j] == quote)
			return ;
		j++;
	}
	syntax_error_msg(3, str);
}

bool	is_white(char c)
{
	char *delims;

	delims = " \t\n";
	while (*delims)
	{
		if (c == *delims)
			return (true);
		delims++;
	}
	return (false);
}

void	check_if_nothing(char *str, int i)
{
	while (str[++i] && is_white(str[i]) == true)
	
}

/*check the syntax error: if there is error, send exit message with
proper exit value. 
can we use exit(258)? I don't know :/ */
int	syntax_error(char *str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (str[0] == '|')
			syntax_error_msg(1, str);
		if ((str[i][j] == '<' || str[i][j] == '>') && !str[i + 1])
			syntax_error_msg(2, str);
		if ((str[i][j] == '<' && str[i][j + 1] == '<') && !str[i + 1])
			syntax_error_msg(2, str);
		if ((str[i][j] == '>' && str[i][j + 1] == '>') && !str[i + 1])
			syntax_error_msg(2, str);
		if (str[i][0] == 34 || str[i][0] == 39)
			quote_check(str, i, str[i][0]);
	}
	return (0);
}
