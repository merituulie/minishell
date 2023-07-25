/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 09:07:23 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/25 15:22:03 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/tests.h"
#include "../unity_src/unity.h"

void test_lexer1(void)
{
	char	*str1 = "cat text.txt | grep 'moi' | wc -l";
	char	*str2 = "cat text.txt|grep 'moi'|wc -l| moi";
	char	*str3 = "";
	char	*str4 = "cat";
	char	*str5 = "cat text.txt \0 grep 'moi' | wc -l";
	char	*expected1[8] = {
	"cat",
	"text.txt",
	"|",
	"grep",
	"'moi'",
	"|",
	"wc",
	"-l"
	};
	char	*expected2[1] = {""};
	char	*expected3[2] = {
	"cat"
	};
	char	*expected4[3] = {
	"cat",
	"text.txt",
	};

	char	**actual1 = ft_lexer(str1);
	char	**actual2 = ft_lexer(str2);
	char	**actual3 = ft_lexer(str3);
	char	**actual4 = ft_lexer(str4);
	char	**actual5 = ft_lexer(str5);

	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, actual1, sizeof(expected1) / sizeof(expected1[0]), "failed str1");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, actual2, sizeof(expected1) / sizeof(expected1[0]), "failed str2");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, actual3, sizeof(expected2) / sizeof(expected2[0]), "failed str3");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, actual4, sizeof(expected3) / sizeof(expected3[0]), "failed str4");
	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, actual5, sizeof(expected4) / sizeof(expected4[0]), "failed str5");
}
