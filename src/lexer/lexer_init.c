/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:31:00 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/23 12:10:45 by jhusso           ###   ########.fr       */
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
	lexer->dq_flag = 0;
	lexer->sq_flag = 0;
}
