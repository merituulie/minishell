/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:46:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/23 12:14:31 by jhusso           ###   ########.fr       */
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
	int	delims[4];
	int	token_count;
	int	dq_flag;
	int	sq_flag;
}	t_lexer;

// lexer.c
bool static	is_delim(int *delims, char c);
static bool	is_same_quote(int d_quote_flag, int s_quote_flag);
static void	count_tokens(char const *str, t_lexer *lexer, int len);
char		**put_array(char **token_array, char *str, t_lexer *lexer);
char		**ft_lexer(char *str);

// lexer_init.c
void		init_set(int *set);
void		init_struct(t_lexer *lexer, char *str);

#endif
