/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 09:59:13 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/22 14:40:27 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define PURPLE "\x1b[38;5;128m"
# define BORING "\x1b[0m"

# include "minishell.h"

# include <stdbool.h>

typedef struct s_env	t_env;

typedef struct s_lexer
{
	int		i;
	int		j;
	int		del_len;
	char	**arr;
	char	**new_arr;
}	t_lexer;

char	**add_line(t_lexer *l);
int		case_operand(t_lexer *l);
bool	is_delim(char c);
bool	is_operand(char c);
int		quote_index(char *str, int j);
int		double_redir(char *str, int j);
int		syntax_error_msg(int i, char *str);
char	**allocate_2d_array(char **old_array);
int		trim_last_line(char **array, int line_index);
int		check_if_nothing(char *str, int i);
int		quote_check(char *str, int i, char quote);
char	**ft_lexer(char *str);
int		syntax_error(char *str, int i);

#endif
