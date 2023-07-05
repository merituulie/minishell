/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:46:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/05 14:57:54 by jhusso           ###   ########.fr       */
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

// lexer.c
size_t	ft_arrlen(const char **array);
bool	is_delim(char c);
char	**add_line(char **old_array, size_t del_index, int del_line_index, size_t del_len);
char	**parse_line(char **array, size_t len);
char	**ft_lexer(char *str);
int		quote_index(char *str, int j);

#endif
