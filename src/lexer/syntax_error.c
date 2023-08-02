/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:47:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/02 13:54:10 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/* 1 is pipe, 2 is < or > or << or >>
error value 258 needs to be returned*/
int	syntax_error_msg(int i, char *str)
{
	if (i == 1)
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
	if (i == 2)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
	if (i == 3)
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	if (i == 4)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	if (i == 5)
		ft_putstr_fd("syntax error: quotes not ended\n", 2);
	free(str);
	error_code(258);
	return (-1);
}

/*if the single quotes or double quotes doesn't have a pair ending
if succee return 0 */
int	syntax_error2(char *str, int i)
{
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i = quote_check(str, i, str[i]);
			if (i == -1)
				return (i);
		}
	}
	return (0);
}

static int	check_pipe_syntax(char *str, int i)
{
	if (str[0] == '|')
		return (syntax_error_msg(1, str));
	else if (str[i] == '|' && str[i + 1] == '|')
		return (syntax_error_msg(1, str));
	else if (str[i] == '|' && check_if_nothing(str, i))
		return (syntax_error_msg(1, str));
	return (0);
}

static int	check_redir_syntax(char *str, int i)
{
	if ((str[i] == '<' || str[i] == '>') && check_if_nothing(str, i))
		return (syntax_error_msg(2, str));
	if ((str[i] == '<' && str[i + 1] == '<') && \
								check_if_nothing(str, i + 1))
		return (syntax_error_msg(2, str));
	else if ((str[i] == '>' && str[i + 1] == '>') && \
								check_if_nothing(str, i + 1))
		return (syntax_error_msg(2, str));
	else if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
		return (syntax_error_msg(3, str));
	else if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<'))
		return (syntax_error_msg(4, str));
	else if (str[i] == '>' && str[i + 1] == '<')
		return (syntax_error_msg(4, str));
	return (0);
}

/*check the syntax error: if there is error, send exit message with
proper exit value.
can we use exit(258)? I don't know :/ */
int	syntax_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
		{
			return (check_pipe_syntax(str, i));
		}
		if (str[i] == '>' || str[i] == '<')
			return (check_redir_syntax(str, i));
	}
	return (syntax_error2(str, i));
}
