# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emeinert <emeinert@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 16:13:53 by meskelin          #+#    #+#              #
#    Updated: 2023/07/22 13:16:39 by emeinert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = ft_bzero \
ft_arrlen \
ft_calloc \
ft_free_null_str \
ft_free_array \
ft_isalnum \
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
ft_substr \
ft_memcpy  \
ft_print_array \
ft_strjoin \
ft_strchr \
ft_strdup \
ft_strlcat \
free_array \
ft_atoi_exit \
ft_isdigit 

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
