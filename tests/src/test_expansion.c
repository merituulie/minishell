// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_expansion.c                                   :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/25 07:31:44 by jhusso            #+#    #+#             */
// /*   Updated: 2023/07/25 15:21:16 by jhusso           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include  "../includes/tests.h"
// #include "../unity_src/unity.h"

// void	test_expand_quote_check(void)
// {
// 	t_data	data;

// 	char	*str1[2] ={
// 	"$USER",
// 	"XXX",
// 	} ;
// 	// char	*str2 = "\'$USER\'";
// 	char	*expected1[2] = {
// 	"jhusso",
// 	"XXX",
// 	} ;
// 	// char	*expected2 = "$USER";

// 	char **actual1 = expand_quote_check(&data, str1);

// 	TEST_ASSERT_EQUAL_STRING_MESSAGE(expected1[0], actual1[0], "failed str1");

// }
