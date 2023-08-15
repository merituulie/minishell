/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:07:21 by meskelin          #+#    #+#             */
/*   Updated: 2023/08/15 11:24:11 by meskelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>

long long	ft_atoll(const char *str);
int			ft_arrlen(char **array);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_free_null_str(char *str);
void		ft_free_array(char **array);
int			ft_isalnum(int c);
char		*ft_itoa(int n);
char		*ft_lltoa(long long n);
int			ft_isalpha(int n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void	*b, int c, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strdup(const char *s1);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strncmp_all(const char *s1, const char *s2);
char		*ft_strtrim(char const *s1, char *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_print_array(char **str);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd, int print_shellname);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s1);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
void		free_char_array(char **str);
int			ft_isdigit(char c);
int			ft_strchr_index(const char *s, int c);
char		*ft_strchr_null(const char *s, int c);
void		ft_putnbr_fd(int n, int fd);
void		free_and_nullify(void *to_be_freed);

#endif
