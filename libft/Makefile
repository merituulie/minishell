# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/08/15 11:24:20 by meskelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = ft_bzero \
ft_arrlen \
ft_calloc \
ft_free_null_str \
ft_free_array \
ft_isalnum \
ft_itoa \
ft_memcpy  \
ft_memset \
ft_print_array \
ft_putchar_fd \
ft_putstr_fd \
ft_split \
ft_strcpy \
ft_strdup \
ft_strlcpy \
ft_strlen \
ft_strncmp \
ft_substr \
ft_strncmp_all \
ft_strtrim \
ft_strjoin \
ft_strchr \
ft_strdup \
ft_strlcat \
free_array \
ft_atoll \
ft_isdigit \
ft_strchr_index \
ft_strchr_null \
ft_putnbr_fd \
ft_isalpha \
ft_lltoa \
free_and_nullify \

H_FILES = libft

LIB_NAME = libft.a

SRC = $(addsuffix .c, $(SRC_FILES))
OBJ = $(addsuffix .o, $(SRC_FILES))
HS = $(addsuffix .h, $(H_FILES))

BUILD_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	cc $(BUILD_FLAGS) -c $(SRC) -I $(HS)
	ar rc $(LIB_NAME) $(OBJ)
	ranlib $(LIB_NAME)

clean:
	rm -f $(OBJ) $(B_SRC:.c=.o)

fclean: clean
	rm -f $(LIB_NAME)

re: fclean all
