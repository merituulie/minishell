/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 13:40:47 by rmakinen          #+#    #+#             */
/*   Updated: 2023/08/08 11:56:19 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// PinkShell color stuffffffff
# define PINK "\x1b[38;2;255;192;203m"
# define BORING "\x1b[0m"

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include "minishell.h"

typedef struct s_env	t_env;

typedef struct s_lexer
{
	int		i;
	int		j;
	int		del_len;
	char	**arr;
	char	**new_arr;
}	t_lexer;

// lexer.c
char	**ft_lexer(char *str);

/*add_lines_lexer.c*/
char	**add_line(t_lexer *l);
int		case_operand(t_lexer *l);

//lexer_utils.c
int		syntax_error_msg(int i, char *str);
char	**allocate_2d_array(char **old_array);
int		trim_last_line(char **array, int line_index);
int		check_if_nothing(char *str, int i);
int		quote_check(char *str, int i, char quote);

//char_checks.c
bool	is_delim(char c);
bool	is_operand(char c);
int		quote_index(char *str, int j);
int		double_redir(char *str, int j);

/*syntax_error.c*/
int		syntax_error(char *str);

#endif
