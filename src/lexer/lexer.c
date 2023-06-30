/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 14:49:55 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/30 10:33:27 by jhusso           ###   ########.fr       */
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
	char	**split_array_de;
	char	**split_array_op;

	init_struct(&lexer, str);
	trimmed_line = ft_strtrim(str, lexer.delims, 4);
	// printf("trimmed line: %s\n", trimmed_line);
	split_array_de = split_de(trimmed_line, &lexer);
	// printf("lexer.token_count: %i\n", lexer.token_count);
	int i = 0;
	while (i < lexer.token_count)
	{
		printf("split_array_de[%i]: %s\n", i, split_array_de[i]);
		i++;
	}
	// printf("HERE\n");
	split_array_op = split_op(split_array_op, split_array_de, &lexer);

}
