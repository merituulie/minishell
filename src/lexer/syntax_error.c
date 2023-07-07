/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:47:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/07 13:14:36 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/* 1 is pipe, 2 is < or > or << or >>
error value 258 needs to be returned*/
void	syntax_error_msg(int i, char *str)
{
	if (i == 1)
		printf("syntax error near unexpected token '|'\n");
	if (i == 2)
		printf("syntax error near unexpected token 'newline'\n");
	if (i == 3)
		printf("syntax error: quotes not ended\n");
	free(str);
	exit(258);
}

/*if the single quotes or double quotes doesn't have a pair ending*/
void	quote_check(char *str, int i, char quote)
{
	printf("comes in to quote_check, index is:%d, quote is %c\n", i, quote);
	i++;
	while (str[i])
	{
		if (str[i] == quote)
			return ;
		i++;
	}
	syntax_error_msg(3, str);
}

bool	is_white(char c)
{
	char	*delims;

	delims = " \t\n";
	while (*delims)
	{
		if (c == *delims)
			return (true);
		delims++;
	}
	return (false);
}

int	check_if_nothing(char *str, int i)
{
	i++;
	while (str[i] && is_white(str[i]) == true)
		i++;
	if (!str[i])
		return (1);
	return (0);
}

/*check the syntax error: if there is error, send exit message with
proper exit value. 
can we use exit(258)? I don't know :/ */
void	syntax_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[0] == '|' && check_if_nothing(str, i))
			syntax_error_msg(1, str);
		if (str[i] == '|' && check_if_nothing(str, i))
			syntax_error_msg(1, str);
		if ((str[i] == '<' || str[i] == '>') && check_if_nothing(str, i))
			syntax_error_msg(2, str);
		if ((str[i] == '<' && str[i + 1] == '<') && check_if_nothing(str, i))
			syntax_error_msg(2, str);
		if ((str[i] == '>' && str[i + 1] == '>') && check_if_nothing(str, i))
			syntax_error_msg(2, str);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			quote_check(str, i, str[i]);
			return ;
		}
	}
}
