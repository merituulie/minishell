/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:56:12 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 10:56:14 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"

int	check_pipe_syntax(char *str, int i)
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
		if (str[i + 1] == '|' || !str[i + 1])
			return (syntax_error_msg(1, str));
	}
	return (0);
}

static int	out_redir_syntax_error(char *str, int i)
{
	if (check_if_nothing(str, i + 1) || str[i + 1] == '|')
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
	if (check_if_nothing(str, i + 1) || str[i + 1] == '|')
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

static int	check_for_pipe_redir(char *str, int i)
{
	int	ret;

	ret = 0;
	if (str[i] == '|')
		ret = check_pipe_syntax(str, i);
	else if (str[i] == '>')
		ret = out_redir_syntax_error(str, i);
	else if (str[i] == '<')
		ret = in_redir_syntax_error(str, i);
	return (ret);
}

/*check the syntax error: if there is error, send exit message with
proper exit value.
can we use exit(258)? I don't know :/ */
int	syntax_error(char *str, int len)
{
	int	ret;
	int	i;

	i = 0;
	while (i < len)
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i = quote_check(str, i + 1, str[i]);
			if (i == -1)
				return (i);
		}
		else
		{
			ret = check_for_pipe_redir(str, i);
			if (ret)
				return (ret);
		}
		i++;
	}
	return (ret);
}
