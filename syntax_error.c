/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:21:30 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/03 17:08:55 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

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
	if (i == 2)
		ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
	if (i == 3)
		ft_putstr_fd("syntax error :quotes not ended\n", 2);
	free_char_array(str);
	exit(258);
}

/*if the single quotes or double quotes doesn't have a pair ending*/
void	quote_check(char *str, char quote)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == quote)
			return ;
	}
	syntax_error_msg(3, str);
}

/*check the syntax error: if there is error, send exit message with
proper exit value. 
can we use exit(258)? I don't know :/ */
int	syntax_error(char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[0][0] == '|' && !str[1])
				syntax_error_msg(1, str);
			if ((str[i][j] == '<' || str[i][j] == '>') && !str[i + 1])
				syntax_error_msg(2, str);
			if ((str[i][j] == '<' && str[i][j + 1] == '<') && !str[i + 1])
				syntax_error_msg(2, str);
			if ((str[i][j] == '>' && str[i][j + 1] == '>') && !str[i + 1])
				syntax_error_msg(2, str);
			if (str[i][0] == 34 || str[i][0] == 39)
				quote_check(str[i], str[i][0]);
		}
	}
	return (0);
}

int	main(void)
{
	char	**str;

	str = malloc(sizeof(char *) * 3);
	str[0] = strdup("|");
	str[1] = strdup("helo");
	str[2] = strdup("\0");
	if (!syntax_error(str))
		printf("no syntax error\n");
	return (0);
}
