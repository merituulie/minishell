/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_char_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 11:28:14 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/22 14:12:46 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/tests.h"
#include "../unity_src/unity.h"

void	test_quote_index(void)
{
	char *str1 = "\"moi\"";
	char *str2 = "\"how are \"you?";
	char *str3 = "how \"are \"you?";
	char *str4 = "\'how are \'you?";
	char *str5 = "\"moi";

	int expected1 = 4;
	int expected2 = 9;
	int expected3 = 0;
	int expected4 = 9;
	int expected5 = 0;
	int expected6 = 0;
	int expected7 = 0;

	int	actual1 = quote_index(str1, 0);
	int	actual2 = quote_index(str2, 0);
	int	actual3 = quote_index(str3, 0);
	int	actual4 = quote_index(str4, 0);
	int	actual5 = quote_index(str5, 0);
	int	actual6 = quote_index(NULL, 0);
	int	actual7 = quote_index("", 0);

	TEST_ASSERT_EQUAL_INT_MESSAGE(expected1, actual1, "failed str1");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected2, actual2, "failed str2");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected3, actual3, "failed str3");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected4, actual4, "failed str4");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected5, actual5, "failed str5");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected6, actual6, "failed str6");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected7, actual7, "failed str7");
}

void	test_double_redir(void)
{
	char *str1 = "<moi"; // 1
	char *str2 = "<<moi"; // 2
	char *str3 = ">moi"; // 1
	char *str4 = ">>moi"; // 2
	char *str5 = "|moi"; // 1
	char *str6 = "||moi"; // 2 do we need to check?
	char *str7 = "m<moi"; // 1
	char *str8 = "moi<<moi"; // 2

	int expected1 = 1;
	int expected2 = 2;
	int expected3 = 1;
	int expected4 = 2;
	int expected5 = 1;
	int expected6 = 2;
	int expected7 = 0;
	int expected8 = 0;

	int actual1 = double_redir(str1, 0);
	int actual2 = double_redir(str2, 0);
	int actual3 = double_redir(str3, 0);
	int actual4 = double_redir(str4, 0);
	int actual5 = double_redir(str5, 0);
	int actual6 = double_redir(str6, 0);
	int actual7 = double_redir(str7, 0);
	int actual8 = double_redir(str8, 0);

	TEST_ASSERT_EQUAL_INT_MESSAGE(expected1, actual1, "failed str1");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected2, actual2, "failed str2");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected3, actual3, "failed str3");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected4, actual4, "failed str4");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected5, actual5, "failed str5");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected6, actual6, "failed str6");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected7, actual7, "failed str7");
	TEST_ASSERT_EQUAL_INT_MESSAGE(expected8, actual8, "failed str8");
}
