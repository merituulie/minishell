/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:21:30 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/03 18:22:09 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s != '\0')
	{
		counter++;
		s++;
	}
	return (counter);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	str = malloc (sizeof(char) *(len + 1));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

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
void	quote_check(char **str, int i, char quote)
{
	int j;

	j = 1;
	while (str[i][j])
	{
		if (str[i][j] == quote)
			return ;
		j++;
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
		printf("here\n");
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
				quote_check(str, i, str[i][0]);
		}
	}
	return (0);
}

int	main(void)
{
	char	**str;

	str = malloc(sizeof(char *) * 4);
	str[0] = ft_strdup("hello");
	str[1] = ft_strdup("<");
	str[2] = ft_strdup("\"hello\'");
	str[3] = ft_strdup("0");
	printf("string str[2] is %s\n", str[2]);
	if (!syntax_error(str))
		printf("no syntax error\n");
	return (0);
}
