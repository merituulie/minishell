/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 14:55:06 by yoonslee          #+#    #+#             */
/*   Updated: 2023/07/25 14:55:09 by yoonslee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// Jose's PinkShell color stuffffffff
# define PINK "\x1b[38;2;255;192;203m"
# define BORING "\x1b[0m"

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include "parsing.h"
# include "minishell.h"
# include "../tests/includes/tests.h"

typedef struct s_env	t_env;

// lexer.c
char	**add_line(char **old_array, size_t del_index, int del_line_index);
char	**add_line_redir(char **array, size_t del_index, \
		int del_line_index, size_t del_len);
char	**parse_line_helper(char ***array, size_t i, size_t j, size_t del_len);
char	**parse_line(char **array);
char	**ft_lexer(char *str, t_env **env);

//lexer_utils.c
char	**allocate_2d_array(char **old_array);
void	trim_last_line(char **array, int line_index);

//char_checks.c
bool	is_delim(char c);
bool	is_operand(char c);
int		quote_index(char *str, int j);
int		double_redir(char *str, int j);

/*syntax_error.c*/
int		syntax_error(char *str, t_env **env);
int		syntax_error2(char *str, int i, t_env **env);
int		quote_check(char *str, int i, char quote, t_env **env);
int		check_if_nothing(char *str, int i);
int		syntax_error_msg(int i, char *str, t_env **env);

#endif
