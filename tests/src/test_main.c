/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 07:48:44 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/25 15:21:25 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/tests.h"
#include "../unity_src/unity.h"

void	setUp(void)
{}

void	tearDown(void)
{}

int	main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_lexer1); // ft_lexer
	RUN_TEST(test_lexer_utils1); // allocate_2d_array
	RUN_TEST(test_lexer_utils2); // trim_last_line

	// RUN_TEST(test_double_redir);
	// RUN_TEST(test_quote_index);
	// RUN_TEST(test_expand_quote_check);


	return UNITY_END();
}
