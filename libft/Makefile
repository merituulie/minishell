# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 16:13:53 by meskelin          #+#    #+#              #
#    Updated: 2023/06/22 12:25:58 by jhusso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_FILES = ft_strlen \
ft_memset \
ft_strncmp \
ft_bzero \
ft_calloc \
ft_strlcpy \
ft_strtrim \

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
