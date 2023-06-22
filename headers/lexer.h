/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:46:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/22 14:50:29 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// Jose's PinkShell color stuffffffff
# define PINK "\x1b[38;2;255;192;203m" //"\x1b[35m"
# define BORING "\x1b[0m"

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

// lexer.c
bool static	is_delim(int *delims, char c);
static bool	is_same_quote(int d_quote_flag, int s_quote_flag);
int			count_tokens(char const *str, int *delims, int len);
char		**ft_trimcmd(char **token_array, char *str, int *delims, \
			int token_count);
char		**ft_lexer(char *str);

// lexer_utils.c
void	init_set(int *set);

#endif
