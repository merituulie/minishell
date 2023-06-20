/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/20 17:05:50 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

bool	is_delim(int *delims, char c)
{
	while (*delims != '\0')
	{
		if (*delims == c)
			return (true);
		delims++;
	}
	return (false);
}

int	count_words(char const *str, int *delims)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	if (str[i] == 0)
		return (0);
	while (str[i] != '\0' && str[i + 1])
	{
		if (is_delim(delims, str[i]) == true)
		{
			if (is_delim(delims, str[i - 1]) == false)
				word_count++;
		}
		if (str[i] == 34)
		{
			i++;
			while (str[i] != 34)
				i++;
			word_count++;
		}
		i++;
	}
	if (is_delim(delims, str[i - 1]) == false && str[i - 1] != 34)
		word_count++;
	return (word_count);
}

// int	word_length(char const *s, int i, char c)
// {
// 	int	size;

// 	size = 0;
// 	while (s[i] != c && s[i])
// 	{
// 		size++;
// 		i++;
// 	}
// 	return (size);
// }

// char	**set_words(char **array, int words, char const *s, int *delims)
// {
// 	int		size;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (i < words)
// 	{
// 		while (s[j] == c)
// 			j++;
// 		size = word_length(s, j, c);
// 		array[i] = malloc(size + 1);
// 		ft_strlcpy(array[i], &s[j], size + 1);
// 		if (array[i] == NULL)
// 		{
// 			while (--i)
// 				free(array[i]);
// 			return (NULL);
// 		}
// 		j = j + size;
// 		i++;
// 	}
// 	return (array);
// }

char	**ft_trimcmd(char const *s, int *delims)
{
	char	**array;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_words(s, delims);
	printf("WORD COUNT: %i\n", words);
	printf("HERE\n");
	// array = (char **)malloc(sizeof(char *) * (words + 1));
	// if (array == NULL)
	// 	return (NULL);
	// array[words] = NULL;
	// // array = set_words(array, words, s, delims);
	// return (array);
}

char	**ft_lexer(char *str)
{
	int delims[] = {9, 32};

	ft_trimcmd(str, delims);
	return (0);

}

