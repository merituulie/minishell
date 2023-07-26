# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jhusso <jhusso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/17 13:26:39 by jhusso            #+#    #+#              #
#    Updated: 2023/07/26 10:57:33 by jhusso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
BUILD_FLAGS = -Wall -Wextra -Werror -lreadline
INCLUDES = -I../headers -I../libft

SRC = test_main \
	test_lexer \
	test_lexer_utils1 \
	test_lexer_utils2 \
	# test_expansion \
	# test_char_checks \

UNITY_SRC = unity

SRC_PRE = $(addprefix src/, $(SRC))
SRC_SUFF = $(addsuffix .c, $(SRC_PRE))
UNITY_PRE = $(addprefix unity_src/, $(UNITY_SRC))
UNITY_SUFF = $(addsuffix .c, $(UNITY_PRE))
H_PRE = $(addprefix includes/, $(H_FILE))
H_SUFF = $(addsuffix .h, $(H_PRE))

MINISHELL =
PS := $(filter-out %main.c, $(MINISHELL))

NAME = tests

all: $(NAME)

$(NAME): compile clean
	$(CC) $(BUILD_FLAGS) $(INCLUDES) $(PS:%=../%) $(SRC_SUFF) $(UNITY_SUFF) -o $(NAME) -L./unity_src -lunity -L../libft -lft
	./tests

compile:
	gcc -c unity_src/unity.c -o unity_src/unity.o
	ar rcs unity_src/libunity.a unity_src/unity.o

clean:
	rm -f $(NAME)
	# rm unity_src/unity.o
	# rm unity_src/libunity.a

