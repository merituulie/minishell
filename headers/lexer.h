/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:46:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/24 18:38:42 by jhusso           ###   ########.fr       */
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

typedef struct s_lexer
{
	int	*delims[4];
	int	*operands[3];
	int	token_count;
	int	op_count;
	int	dq_flag;
	int	sq_flag;
}	t_lexer;

// lexer.c
void		init_delim_set(int *set);
void		init_struct(t_lexer *lexer, char *str);
char		**ft_lexer(char *str);

// split_delims.c
static	char	is_set(char const c, int *set);
bool static	is_delim(int *delims, char c);
static bool	is_same_quote(int d_quote_flag, int s_quote_flag);
void		count_tokens_de(char const *str, t_lexer *lexer, int len);
char		**split_de(char **split_array_de, char *str, t_lexer *lexer);

// split_operands.c
static bool	is_operand(int *operands, char c);
static bool	over_one_op(char *str, int i);
static void	count_op(char const *str, t_lexer *lexer, int len);
static int	set_string(char *split_array_op, char *split_array_de, int k, t_lexer *lexer);
char		**put_array_op(char **split_array_op, char **split_array_de, t_lexer *lexer);
char		**split_op(char **split_array_de, t_lexer *lexer);
#endif
