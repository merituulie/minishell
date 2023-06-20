/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/20 10:17:47 by jhusso           ###   ########.fr       */
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
	int	tokens;
	int	i;
	int	j;

	nb_words = 0;
	tokens = 0;
	i = 0;
	if (str[i] == 0)
		return (0);
	while (str[i] != '\0' && str[i + 1])
	{
		j = 0;
		while (str[i] == 32 || str[i] == 9) // need to add str[i] == 10 || str[i] == 59 ??
		{
			if (str[i - 1] != 32 && str[i - 1] != 9)
				nb_words++;
			i++;
		}
		if (str[i] == 124 || str[i] == 60 || str[i] == 47 || str[i] == 62)
		{
			i++;
			tokens++;
			if (str[i - 1] != 32 && str[i - 1] != 9)
				nb_words++;
		}
		i++;
	}
	if (str[i] != delimeters[i])
		nb_words++;
	return (nb_words + tokens);
}

int	word_length(char const *s, int j)
{
	int	size;

	size = 0;
	while (s[j] != 9 && s[j] != 32 && s[j])
	{
		if (s[j] == 124 || s[j] == 60 || s[j] == 47 || s[j] == 62)
		{
			size++;
			return (size);
		}
		else
		{
			size++;
			j++;
		}
	}
	j++;
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
	// printf("words in set_word: %d\n", words);
	while (i < words)
	{
		while (s[j] == 9 || s[j] == 32)
		{
			// printf("HERE\n");
			j++;
		}
		// printf("before j = %i\n", j);
		// printf("s[j] == %c\n", s[j]);
		size = word_length(s, j);
		// printf("%i word len = %i\n", i+1, size);
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
