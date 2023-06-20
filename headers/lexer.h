/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:46:20 by jhusso            #+#    #+#             */
/*   Updated: 2023/06/20 15:28:17 by jhusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// jose's PinikShell color stuffffffff
# define PINK "\x1b[38;2;255;192;203m" //"\x1b[35m"
# define BORING "\x1b[0m"

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
// # include <stdbool.h>

int		count_words(char const *str, char c);
int		word_length(char const *s, int i, char c);
char	**set_words(char **array, int words, char const *s, char c);
char	**ft_trimcmd(char const *s, int *delims);
char	**ft_lexer(char *str);

#endif
