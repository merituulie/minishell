# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 13:37:28 by yoonslee          #+#    #+#              #
#    Updated: 2023/03/07 15:18:32 by yoonslee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c\
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_tolower.c ft_toupper.c\
ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c\
ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
ft_split.c ft_printf.c ft_printf_utils.c ft_printf_ptr.c ft_printf_hex.c ft_lstnew_bonus.c\
ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c\
get_next_line.c get_next_line_bonus.c ft_split_one_str_out.c

OBJS = $(SRCS:.c=.o)

HEADER = libft.h
CC = cc
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):$(OBJS)
		ar rcs $(NAME) $(OBJS)
		ranlib $(NAME)

$(OBJS):$(SRCS)
		${CC} -c ${FLAGS} $(SRCS) -I $(HEADER)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all, bonus, clean, fclean, re