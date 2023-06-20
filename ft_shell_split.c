/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/20 14:21:12 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h> //-lreadline

#define PINK "\x1b[38;2;255;192;203m" //"\x1b[35m"
#define BORING "\x1b[0m"

// /*Does not handle quotes*/

int	count_words(char const *str, char c)
{
	int	nb_words;

	nb_words = 0;
	if (*str == 0)
		return (0);
	while (*str != '\0' && *(str + 1))
	{
		if (*str != c)
		{
			if (*(str + 1) == c || *(str + 1) == '\0')
				nb_words++;
		}
		str++;
	}
	if (*str != c)
		nb_words++;
	return (nb_words);
}

int	word_length(char const *s, int i, char c)
{
	int	size;

	size = 0;
	while (s[i] != c && s[i])
	{
		size++;
		i++;
	}
	return (size);
}

char	**set_words(char **array, int words, char const *s, char c)
{
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] == c)
			j++;
		size = word_length(s, j, c);
		array[i] = malloc(size + 1);
		ft_strlcpy(array[i], &s[j], size + 1);
		if (array[i] == NULL)
		{
			while (--i)
				free(array[i]);
			return (NULL);
		}
		j = j + size;
		i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (array == NULL)
		return (NULL);
	array[words] = NULL;
	array = set_words(array, words, s, c);
	return (array);
}

int main(void)
{
	char	**tokens;
	// int delim = 9;

	int i = 0;
	tokens = ft_split(readline(PINK "Jose's PinkShell >> " BORING), 32);
	// // printf("%s\n", av[1]);
	while (tokens[i])
	{
		printf("%i = %s\n", i, tokens[i]);
		i ++;
	}
	return (0);
}
