/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:47:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/25 15:29:55 by jhusso           ###   ########.fr       */
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
	// reset_error_code(env);
	return (-1);
}

int	quote_check(char *str, int i, char quote)
{
	i++;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (syntax_error_msg(5, str));
}

/*if the single quotes or double quotes doesn't have a pair ending*/
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

int	check_if_nothing(char *str, int i)
{
	i++;
	while (str[i] && is_delim(str[i]) == true)
		i++;
	if (!str[i])
		return (1);
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
		if ((str[0] == '|' && check_if_nothing(str, i)) || \
			(str[i] == '|' && str[i + 1] == '|'))
			return (syntax_error_msg(1, str));
		else if (str[i] == '|' && check_if_nothing(str, i))
			return (syntax_error_msg(1, str));
		else if ((str[i] == '<' || str[i] == '>') && check_if_nothing(str, i))
			return (syntax_error_msg(2, str));
		else if ((str[i] == '<' && str[i + 1] == '<') && \
									check_if_nothing(str, i + 1))
			return (syntax_error_msg(2, str));
		else if ((str[i] == '>' && str[i + 1] == '>') && \
									check_if_nothing(str, i + 1))
			return (syntax_error_msg(2, str));
		else if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
			return (syntax_error_msg(3, str));
		else if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<'))
			return (syntax_error_msg(4, str));
	}
	return (syntax_error2(str, i));
}
