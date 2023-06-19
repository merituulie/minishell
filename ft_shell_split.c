/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/19 14:42:32 by jhusso           ###   ########.fr       */
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

/*Does not handle quotes*/

int	count_words(char const *str, int *delimeters)
{
	int	nb_words;
	int	i;

	nb_words = 0;
	if (*str == 0)
		return (0);
	while (*str != '\0' && *(str + 1))
	{
		i = 0;
		while (delimeters[i] != '\0')
		{
			if (delimeters[i] == *str )
				nb_words++;
			i ++;
		}
		if (*str == 124 || *str == 60 || *str == 47 || *str == 62)
			nb_words++;
		str++;
	}
	if (*str != delimeters[i])
		nb_words++;
	return (nb_words);
}

int	word_length(char const *s, int i, int *delimeters)
{
	int	size;
	int	j;

	size = 0;
	while (s[i])
	{
		j = 0;
		while (delimeters[j] != '\0')
		{
			if (s[i] == delimeters[j])
				return (size);
			else
				j++;
		}
		size++;
		i++;
	}
	return (size);
}

bool	is_delimeter(int *delimeters, char c)
{
	while (*delimeters != '\0')
	{
		if (*delimeters == c)
			return (true);
		delimeters ++;
	}
	return (false);
}

char	**set_words(char **array, int words, char const *s, int *delimeters)
{
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// printf("string in set_word: %s\n", s);
	while (i < words)
	{
		while (is_delimeter(delimeters, s[j]) == true)
		{
			j++;
		}
		printf("j = %i\n", j);
		size = word_length(s, j, delimeters);
		// printf("word length: %i\n", size);
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

char	**ft_shell_split(char const *s, int *delimeters)
{
	char	**array;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_words(s, delimeters);
	printf("word count: %i\n", words);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (array == NULL)
		return (NULL);
	array[words] = NULL;
	array = set_words(array, words, s, delimeters);
	return (array);
}


int main(void)
{
	char	**tokens;
	int delim[] = {32, 9, 10, 59};
	int i = 0;

	tokens = ft_shell_split(readline(PINK "Jose's PinkShell >> " BORING), delim);
	// printf("%s\n", av[1]);
	while (tokens[i])
	{
		printf("%s\n", tokens[i]);
		i ++;
	}
	return (0);
}
