/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/24 10:00:15 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

void	init_set(int *set)
{
	set[0] = 32;
	set[1] = 9;
	set[2] = 10;
	set[3] = 59;
}

void	init_struct(t_lexer *lexer, char *str)
{
	init_set(lexer->delims);
	lexer->token_count = 0;
	lexer->op_count = 0;
	lexer->dq_flag = 0;
	lexer->sq_flag = 0;
}

char	**ft_lexer(char *str)
{
	t_lexer	lexer;
	char	*trimmed_line;
	char	**put_array;
	char	**trimmed_array;
	int		i;

	init_struct(&lexer, str);
	trimmed_line = ft_strtrim(str, lexer.delims);
	count_tokens_de(trimmed_line, &lexer, ft_strlen(trimmed_line));
	put_array = ft_calloc(lexer.token_count + 1, sizeof(char *));
	if (!put_array)
		return (-1);
	put_array = split_de(put_array, trimmed_line, &lexer);
	free (trimmed_line);
	trimmed_array = ft_calloc(lexer.token_count + 1, sizeof(char *));
	if (!trimmed_array)
		return (-1);
	i = 0;
	while (i < lexer.token_count)
	{
		trimmed_array[i] = ft_strtrim(put_array[i], lexer.delims);
		printf("%s\n", trimmed_array[i]);
		i++;
	}
	ft_free_array(put_array);
	split_op(trimmed_array, &lexer);
	return (0);
}
