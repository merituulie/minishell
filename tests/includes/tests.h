/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:28:54 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/25 10:24:30 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include "../../headers/minishell.h"
# include "../../headers/hashmap.h"
# include "../../headers/lexer.h"
# include "../../headers/parsing.h"
# include "./../unity_src/unity.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <stdio.h>
# include <stdlib.h>

// test_expansion.c
void	test_expand_quote_check(void);

// // test_lexer.c
// void	test_lexer1(void);

// // test_lexer_utils1.c
// char	**allocate_2d_array_test(char **old_array);
// void	test_lexer_utils1(void);

// // test_lexer_utils2.c
// void	test_lexer_utils2(void);
// char	**trim_last_line_test(char **array, int line_index);

// // test_char_checks.c
// void	test_quote_index(void);
// void	test_double_redir(void);

#endif
