/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:47:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/24 07:55:06 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/* 1 is pipe, 2 is < or > or << or >>
error value 258 needs to be returned*/
void	syntax_error_msg(int i, char *str)
{
	if (i == 1)
		// perror("syntax error near unexpected token '|'\n\n");
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		// printf("%s\n", strerror(errno));
	if (i == 2)
		printf("syntax error near unexpected token 'newline'\n");
	if (i == 3)
		printf("syntax error near unexpected token `>'\n");
	if (i == 4)
		printf("syntax error near unexpected token `<'\n");
	if (i == 5)
		printf("syntax error: quotes not ended\n");
	free(str);
	exit(258);
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
	syntax_error_msg(5, str);
	return (-1);
}

/*if the single quotes or double quotes doesn't have a pair ending*/
void	syntax_error2(char *str, int i)
{
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i = quote_check(str, i, str[i]);
			if (i == -1)
				printf("didn't go to syntax_error_msg!\n");
		}
	}
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
void	syntax_error(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[0] == '|' && check_if_nothing(str, i)) || \
			(str[i] == '|' && str[i + 1] == '|'))
			syntax_error_msg(1, str);
		if (str[i] == '|' && check_if_nothing(str, i))
			syntax_error_msg(1, str);
		if ((str[i] == '<' || str[i] == '>') && check_if_nothing(str, i))
			syntax_error_msg(2, str);
		if ((str[i] == '<' && str[i + 1] == '<') && check_if_nothing(str, i))
			syntax_error_msg(2, str);
		if ((str[i] == '>' && str[i + 1] == '>') && check_if_nothing(str, i))
			syntax_error_msg(2, str);
		if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
			syntax_error_msg(3, str);
		if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<'))
			syntax_error_msg(4, str);
	}
	syntax_error2(str, i);
}
