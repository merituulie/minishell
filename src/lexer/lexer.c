/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/21 08:15:20 by jhusso           ###   ########.fr       */
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

// considers only double quotes for now!

int	count_words(char const *str, int *delims)
{
	int	len;
	int	word_count;
	int	quote_flag;
	int	i;
	len = ft_strlen(str);
	word_count = 0;
	quote_flag = 0;
	i = 0;
	if (!str)
		return (0);
	while (i < len)
	{
		if (str[i] == 34) // || str[i] == 39
				quote_flag = !quote_flag;
		else if (is_delim(delims, str[i]) == true && !quote_flag)
				word_count++;
		i++;
	}
	if (i == len)
		word_count++;
	// printf("words= %i\n", word_count);
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

char	**ft_trimcmd(char const *str, int *delims)
{
	int	quote_flag;
	int	i;


	quote_flag = 0;
	while (i < len)
	{
		if (str[i] == 34 || str[i] == 39)
			quote_flag = !quote_flag;
		else if (is_delim(delims, str[i]) == true)
		{

		}
		i++;
	}
}

char	**ft_lexer(char *str)
{
	int		delims[] = {9, 32}; // , 10, 59
	int		word_count;
	char	**trimcmd_tokens;

	word_count = count_words(str, delims);
	trimcmd_tokens = calloc(word_count + 1, sizeof(char *));
	if (!trimcmd_tokens)
		return (-1);
	trimcmd_tokens = ft_trimcmd(str, delims);
	return (0);

}

