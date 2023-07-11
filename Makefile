# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 17:41:46 by meskelin          #+#    #+#              #
#    Updated: 2023/07/11 08:26:12 by rmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_PATH = ./libft

BUILD_FLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -g

HASHMAP_SRC = add_hashmap \
				clear_hashmap \
				utils_hashmap \

ENV_SRC = init \
		env

BUILT_SRC = echo

H_FILES = hashmap \
		env \
		minishell

HASHMAP_PRE = $(addprefix ./src/hashmap/, $(HASHMAP_SRC))
HASHMAP_SUFF = $(addsuffix .c, $(HASHMAP_PRE))
ENV_PRE = $(addprefix ./src/env/, $(ENV_SRC))
ENV_SUFF = $(addsuffix .c, $(ENV_PRE))
HPRE = $(addsuffix ./headers/, $(H_FILES))
HSUFF = $(addsuffix .h, $(HPRE))
BUILT_PRE = $(addprefix ./src/builtins/, $(BUILT_SRC))
BUILT_SUFF = $(addsuffix .c, $(BUILT_PRE))

.PHONY = all
all: $(NAME)

$(NAME):
	make -C $(LIBFT_PATH)
	cc $(BUILD_FLAGS) $(HASHMAP_SUFF) $(ENV_SUFF) $(BUILT_SUFF) ./src/command_handler.c main.c \
	-L $(LIBFT_PATH) -lft -o $(NAME)

.PHONY: clean
clean:
	make fclean -C $(LIBFT_PATH)
	rm -f $(SRCSO)

.PHONY: fclean
fclean: clean
	make clean -C $(LIBFT_PATH)
	rm -f $(NAME)

.PHONY: re
re: fclean all

