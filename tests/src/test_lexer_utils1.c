// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test_lexer_utils1.c                                :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/22 07:36:42 by jhusso            #+#    #+#             */
// /*   Updated: 2023/07/25 09:53:57 by jhusso           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include  "../includes/tests.h"
// #include "../unity_src/unity.h"

// // char	**allocate_2d_array_test(char **old_array)
// // {
// // 	char	**new_array;
// // 	size_t	arr_len;

// // 	if (old_array == NULL || !old_array[0])
// // 		return (NULL);
// // 	arr_len = ft_arrlen(old_array);
// // 	new_array = (char **)ft_calloc(arr_len + 2, sizeof(char *));
// // 	if (!new_array)
// // 		return (NULL);
// // 	return (new_array);
// // }
// char **init_large_array(void)
// {
// 	int	rows = 10000;
// 	int	cols = 10000;
// 	int i = 0;

// 	char **large_array = (char **)ft_calloc(rows + 1, sizeof(char *));
// 	if (!large_array)
// 		return (NULL);
// 	while (i < rows)
// 	{
// 		large_array[i] = (char *)ft_calloc(cols + 1, sizeof(char));
// 		if (!large_array[i])
// 			return(NULL);
// 		ft_memset(large_array[i], 'A', cols);
// 		i++;
// 	}
// 	return (large_array);
// }

// void	test_lexer_utils1(void)
// {
// 	char	*old_array1[8] = {
// 	"cat",
// 	"text.txt",
// 	"|",
// 	"grep",
// 	"'moi'",
// 	"|",
// 	"wc",
// 	"-l"
// 	};
// 	char	**old_array2 = NULL;
// 	char	*old_array3[3] = {};
// 	char	**old_array4 = init_large_array();

// 	char **actual1 = allocate_2d_array(old_array1);
// 	char **actual2 = allocate_2d_array(old_array2);
// 	char **actual3 = allocate_2d_array(old_array3);
// 	char **actual4 = allocate_2d_array(old_array4);

// 	TEST_ASSERT_NOT_NULL_MESSAGE(actual1, "failed old_array1");
// 	TEST_ASSERT_NULL_MESSAGE(actual2, "failed NULL array"); //compare to error message
// 	TEST_ASSERT_NULL_MESSAGE(actual3, "failed empty array"); // compare to error message
// 	TEST_ASSERT_NOT_NULL_MESSAGE(actual4, "failed large array");
// 	// free_str_array(old_array1);
// 	free_str_array(old_array4);
// }
