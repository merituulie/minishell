/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/20 15:28:04 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

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

char	**ft_trimcmd(char const *s, int *delims)
{
	char	**array;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_words(s, delims);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (array == NULL)
		return (NULL);
	array[words] = NULL;
	array = set_words(array, words, s, delims);
	return (array);
}

char	**ft_lexer(char *str)
{
	int delims[] = {9, 32};

	printf("TESTING\n");

	// ft_trimcmd(str, delims);

}

