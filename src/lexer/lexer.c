/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/25 09:50:26 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/lexer.h"
#include "../../libft/libft.h"

void	init_delim_set(int *set)
{
	set[0] = 32;
	set[1] = 9;
	set[2] = 10;
	set[3] = 59;
}

void	init_operand_set(int *set)
{
	set[0] = 124;
	set[1] = 62;
	set[2] = 60;
}

void	init_struct(t_lexer *lexer, char *str)
{
	init_delim_set(lexer->delims);
	init_operand_set(lexer->operands);
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
	char	**split_array_de;
	int		i;

	init_struct(&lexer, str);
	trimmed_line = ft_strtrim(str, lexer.delims, 4);
	// printf("trimmed line: %s\n", trimmed_line);
	count_tokens_de(trimmed_line, &lexer, ft_strlen(trimmed_line));
	put_array = ft_calloc(lexer.token_count + 1, sizeof(char *));
	if (!put_array)
		return (-1);
	put_array = split_de(put_array, trimmed_line, &lexer);
	// i = 0;
	// while (i < lexer.token_count)
	// {
	// 	printf("put array[%i]: %s\n", i, put_array[i]);
	// 	i++;
	// }
	free (trimmed_line);
	split_array_de = ft_calloc(lexer.token_count + 1, sizeof(char *));
	if (!split_array_de)
		return (-1);
	i = 0;
	while (i < lexer.token_count)
	{
		// printf("before first phase: %s\n", put_array[i]);
		split_array_de[i] = ft_strtrim(put_array[i], lexer.delims, 4);
		// printf("After first phase: %s\n", split_array_de[i]);
		i++;
	}
	ft_free_array(put_array);
	split_op(split_array_de, &lexer);
	return (0);
}
