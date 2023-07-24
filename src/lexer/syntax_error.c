/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:47:29 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/24 11:00:25 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

/* 1 is pipe, 2 is < or > or << or >>
error value 258 needs to be returned*/
void	syntax_error_msg(int i, char *str, t_env *env)
{
	if (i == 1)
		printf("syntax error near unexpected token '|'\n");
	if (i == 2)
		printf("syntax error near unexpected token 'newline'\n");
	if (i == 3)
		printf("syntax error near unexpected token `>'\n");
	if (i == 4)
		printf("syntax error near unexpected token `<'\n");
	if (i == 5)
		printf("syntax error: quotes not ended\n");
	free(str);
	we_exit(258, env);
}

int	quote_check(char *str, int i, char quote, t_env *env)
{
	i++;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	syntax_error_msg(5, str, env);
	return (-1);
}

/*if the single quotes or double quotes doesn't have a pair ending*/
void	syntax_error2(char *str, int i, t_env *env)
{
	i = -1;
	while (str[++i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i = quote_check(str, i, str[i], env);
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
void	syntax_error(char *str, t_env *env)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[0] == '|' && check_if_nothing(str, i)) || \
			(str[i] == '|' && str[i + 1] == '|'))
			syntax_error_msg(1, str, env);
		if (str[i] == '|' && check_if_nothing(str, i))
			syntax_error_msg(1, str, env);
		if ((str[i] == '<' || str[i] == '>') && check_if_nothing(str, i))
			syntax_error_msg(2, str, env);
		if ((str[i] == '<' && str[i + 1] == '<') && check_if_nothing(str, i))
			syntax_error_msg(2, str, env);
		if ((str[i] == '>' && str[i + 1] == '>') && check_if_nothing(str, i))
			syntax_error_msg(2, str, env);
		if ((str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>'))
			syntax_error_msg(3, str, env);
		if ((str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<'))
			syntax_error_msg(4, str, env);
	}
	syntax_error2(str, i, env);
}
