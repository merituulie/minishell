/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:47:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/08/14 11:48:27 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/*if the single quotes or double quotes doesn't have a pair ending
if succee return 0 */
static int	syntax_error2(char *str, int i)
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
	else
	{
		while (is_delim(str[i + 1]) == true)
			i++;
		if (str[i + 1] == '|')
			return (syntax_error_msg(1, str));
	}
	return (0);
}

static int	out_redir_syntax_error(char *str, int i)
{
	if (check_if_nothing(str, i + 1))
		return (syntax_error_msg(2, str));
	else if ((str[i + 1] == '>') && check_if_nothing(str, i))
		return (syntax_error_msg(2, str));
	else if ((str[i + 1] == '>' && str[i + 2] == '>'))
		return (syntax_error_msg(3, str));
	else if (str[i + 1] == '<')
		return (syntax_error_msg(4, str));
	else
	{
		while (is_delim(str[i + 1]) == true)
			i++;
		if (str[i + 1] == '<')
			return (syntax_error_msg(4, str));
		if (str[i + 1] == '>' && str[i] != '>')
			return (syntax_error_msg(3, str));
	}
	return (0);
}

static int	in_redir_syntax_error(char *str, int i)
{
	if (check_if_nothing(str, i + 1))
		return (syntax_error_msg(2, str));
	else if ((str[i + 1] == '<') && check_if_nothing(str, i))
		return (syntax_error_msg(2, str));
	else if ((str[i + 1] == '<' && str[i + 2] == '<'))
		return (syntax_error_msg(4, str));
	else if (str[i + 1] == '>')
		return (syntax_error_msg(4, str));
	else
	{
		while (is_delim(str[i + 1]) == true)
			i++;
		if (str[i + 1] == '>')
			return (syntax_error_msg(3, str));
		if (str[i + 1] == '<' && str[i] != '<')
			return (syntax_error_msg(4, str));
	}
	return (0);
}

/*check the syntax error: if there is error, send exit message with
proper exit value.
can we use exit(258)? I don't know :/ */
int	syntax_error(char *str)
{
	int	i;
	int	ret;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '|')
			return (check_pipe_syntax(str, i));
		if (str[i] == '>')
		{
			ret = out_redir_syntax_error(str, i);
			if (ret)
				return (ret);
		}
		if (str[i] == '<')
		{
			ret = in_redir_syntax_error(str, i);
			if (ret)
				return (ret);
		}
	}
	return (syntax_error2(str, i));
}
