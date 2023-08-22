# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meskelin <meskelin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/22 10:53:11 by meskelin          #+#    #+#              #
#    Updated: 2023/08/22 10:53:12 by meskelin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = free_and_nullify \
	ft_free_array \
	free_char_array \
	ft_arrlen \
	ft_atoll \
	ft_bzero \
	ft_calloc \
	ft_free_array \
	ft_free_null_str \
	ft_isalnum \
	ft_isalpha \
	ft_isdigit \
	ft_itoa \
	ft_lltoa \
	ft_memcmp \
	ft_memcpy \
	ft_memset \
	ft_putchar_fd \
	ft_putnbr_fd \
	ft_putstr_fd \
	ft_split \
	ft_strchr_index \
	ft_strchr_null \
	ft_print_array \
	ft_strchr \
	ft_strdup \
	ft_strjoin \
	ft_strlcat \
	ft_strlcpy \
	ft_strlen \
	ft_strncmp_all \
	ft_strncmp \
	ft_strtrim \
	ft_strcpy \
	ft_substr \
	malloc_error \

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
