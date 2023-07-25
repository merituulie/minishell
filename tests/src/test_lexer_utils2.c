// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_lexer_utils2.c                                :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/22 07:36:42 by jhusso            #+#    #+#             */
// /*   Updated: 2023/07/25 09:53:45 by jhusso           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include  "../includes/tests.h"
// #include "../unity_src/unity.h"

// char	**trim_last_line_test(char **array, int line_index)
// {
// 	char	*new_last_line;

// 	if (array[line_index][0] == 32 || array[line_index][0] == 9)
// 	{
// 		new_last_line = ft_strtrim(array[line_index], " \t\n");
// 		// free(array[line_index]);
// 		array[line_index] = new_last_line;
// 	}
// 	return (array);
// }

// /* trim_last_line trims last line of array, only if the first character of the line eis tab or space */
// void	test_lexer_utils2(void)
// {
// 	char	*arr_s1[8] = {
// 	"cat",
// 	"text.txt",
// 	"|",
// 	"grep",
// 	"'moi'",
// 	"|",
// 	"wc",
// 	"    -l"
// 	};
// 	char	*arr_s2[7] = {
// 	"cat",
// 	"text.txt",
// 	"|",
// 	"grep",
// 	"'moi'",
// 	"|",
// 	"           wc -l",
// 	};
// 	// char	*arr_s3[8] = {
// 	// "cat",
// 	// "text.txt",
// 	// "|",
// 	// "grep",
// 	// "'moi'",
// 	// "|",
// 	// "wc",
// 	// "-l   "
// 	// };
// 	char	*arr_t1[8] = {
// 	"cat",
// 	"text.txt",
// 	"|",
// 	"grep",
// 	"'moi'",
// 	"|",
// 	"wc",
// 	"	-l"
// 	};
// 	char	*arr_t2[7] = {
// 	"cat",
// 	"text.txt",
// 	"|",
// 	"grep",
// 	"'moi'",
// 	"|",
// 	"			wc -l",
// 	};
// 	// char	*arr_t3[8] = {
// 	// "cat",
// 	// "text.txt",
// 	// "|",
// 	// "grep",
// 	// "'moi'",
// 	// "|",
// 	// "wc",
// 	// "-l	"
// 	// };
// 	char	*expected1[8] = {
// 	"cat",
// 	"text.txt",
// 	"|",
// 	"grep",
// 	"'moi'",
// 	"|",
// 	"wc",
// 	"-l"
// 	};
// 	char	*expected2[7] = {
// 	"cat",
// 	"text.txt",
// 	"|",
// 	"grep",
// 	"'moi'",
// 	"|",
// 	"wc -l"
// 	};

// 	char	**actual_s1 = trim_last_line_test(arr_s1, 7);
// 	char	**actual_s2 = trim_last_line_test(arr_s2, 6);
// 	// char	**actual_s3 = trim_last_line_test(arr_s3, 7);
// 	char	**actual_t1 = trim_last_line_test(arr_t1, 7);
// 	char	**actual_t2 = trim_last_line_test(arr_t2, 6);
// 	// char	**actual_t3 = trim_last_line_test(arr_t3, 7);
// 	// char	**actual2 = ft_lexer(str2);
// 	// char	**actual3 = ft_lexer(str3);
// 	// char	**actual4 = ft_lexer(str4);
// 	// char	**actual5 = ft_lexer(str5);

// 	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, actual_s1, sizeof(expected1) / sizeof(expected1[0]), "failed arr_s1");
// 	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, actual_s2, sizeof(expected2) / sizeof(expected2[0]), "failed arr_s2");
// 	// TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, actual_s3, sizeof(expected1) / sizeof(expected1[0]), "failed arr_s3");
// 	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, actual_t1, sizeof(expected1) / sizeof(expected1[0]), "failed arr_t1");
// 	TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, actual_t2, sizeof(expected2) / sizeof(expected2[0]), "failed arr_t2");
// 	// TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected1, actual_t3, sizeof(expected1) / sizeof(expected1[0]), "failed arr_t3");
// 	// TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected2, actual3, sizeof(expected2) / sizeof(expected2[0]), "failed str3");
// 	// TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected3, actual4, sizeof(expected3) / sizeof(expected3[0]), "failed str4");
// 	// TEST_ASSERT_EQUAL_STRING_ARRAY_MESSAGE(expected4, actual5, sizeof(expected4) / sizeof(expected4[0]), "failed str5");
// }
