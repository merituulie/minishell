/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:46:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/07/06 10:23:41 by jhusso           ###   ########.fr       */
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
char	**add_line(char **old_array, size_t del_index, int del_line_index);
char	**add_line_redir(char **old_array, size_t del_index, int del_line_index, size_t del_len);
bool	is_operand(char c);
char	**parse_line(char **array, size_t len);
char	**ft_lexer(char *str);

//lexer_utils.c
bool	is_delim(char c);
char	**allocate_2d_array(char **old_array);
void	**trim_last_line(char **array, int line_index);
int		quote_index(char *str, int j);
int		double_redir(char *str, int j);

/*syntax_error.c*/
void	syntax_error(char *str);
int		check_if_nothing(char *str, int i);
bool	is_white(char c);
void	syntax_error_msg(int i, char *str);

#endif
