/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/21 11:28:02 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

bool	is_delim(int *delims, char c)
{
	while (*delims != '\0')
	{
		if (*delims == c)
		{
			// printf("returning true\n");
			return (true);
		}
		delims++;
	}
	// printf("returning false\n");
	return (false);
}

// considers only double quotes for now!

int	count_tokens(char const *str, int *delims)
{
	int	len;
	int	token_count;
	int	quote_flag;
	int	i;
	int start = 0;

	len = ft_strlen(str);
	// printf("LEN=%i\n", len);
	token_count = 0;
	quote_flag = 0;
	i = 0;
	if (!str)
		return (0);
	while (i < len)
	{
		if (str[i] == 34 || str[i] == 39)
				quote_flag = !quote_flag;
		else if (is_delim(delims, str[i]) == true && quote_flag == 0)
		{
			token_count++;
			// printf("HERE token count %i\ni = %i\n", token_count, i);
		}
		i++;
	}
	if (str[i] == '\0' && is_delim(delims, str[i-1]) == false)
		token_count++;
	printf("tokens= %i\n", token_count);
	return (token_count);
}

char	**ft_trimcmd(char **token_array, char *str, int *delims, int token_count)
{
	int	quote_flag;
	int	start;
	int	i;
	int	j;

	quote_flag = 0;
	start = 0;
	i = 0;
	j = 0;
	while (j < token_count && str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			quote_flag = !quote_flag;
		else if (is_delim(delims, str[i]) == true && quote_flag == 0)
		{
			token_array[j] = ft_calloc((i - start + 1), sizeof(char *));
			if (!token_array[j])
				return (0);
			// printf("HERE\n");
			ft_strlcpy(token_array[j], &str[start], (i - start + 1));
			// printf("start index= %i\n", start);
			// printf("i index= %i\n", i);
			// printf("TALLENNETTU SANA%i: %s\n", j, token_array[j]);
			start = i + 1;
			j++;
		}
		i++;
	}
	if (str[i] == '\0')
	{
		token_array[j] = ft_calloc((i - start + 1), sizeof(char *));
		if (!token_array[j])
			return (0);
		// printf("HERE\n");
		ft_strlcpy(token_array[j], &str[start], (i - start + 1));
		// printf("start index= %i\n", start);
		// printf("i index= %i\n", i);
		// printf("TALLENNETTU SANA%i: %s\n", j, token_array[j]);
	}
}

char	**ft_lexer(char *str)
{
	int		delims[] = {9, 32}; // , 10, 59
	int		token_count;
	char	**trimcmd_array;

	token_count = count_tokens(str, delims);
	trimcmd_array = ft_calloc(token_count + 1, sizeof(char *));
	if (!trimcmd_array)
		return (-1);
	trimcmd_array = ft_trimcmd(trimcmd_array, str, delims, token_count);
	//PRINTING ARRAY
	int i = 0;
	while (i <token_count)
	{
		printf("%s\n", trimcmd_array[i]);
		i++;
	}
	// PRINTING ARRAY
	return (0);

}

