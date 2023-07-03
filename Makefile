# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/20 17:41:46 by meskelin          #+#    #+#              #
#    Updated: 2023/07/03 13:55:45 by yoonslee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_PATH = ./libft

BUILD_FLAGS = -Wall -Wextra -Werror -g

HASHMAP_SRC = add_hashmap \
				clear_hashmap \
				utils_hashmap

ENV_SRC = init

PARSER_SRC = expand_env

H_FILES = hashmap \
		env \
		parsing

HASHMAP_PRE = $(addprefix ./src/hashmap/, $(HASHMAP_SRC))
HASHMAP_SUFF = $(addsuffix .c, $(HASHMAP_PRE))
ENV_PRE = $(addprefix ./src/env/, $(ENV_SRC))
ENV_SUFF = $(addsuffix .c, $(ENV_PRE))
PARSER_PRE = $(addprefix ./src/parser/, $(PARSER_SRC))
PARSER_SUFF = $(addsuffix .c, $(PARSER_PRE))
HPRE = $(addsuffix ./headers/, $(H_FILES))
HSUFF = $(addsuffix .h, $(HPRE))

.PHONY = all
all: $(NAME)

$(NAME):
	make -C $(LIBFT_PATH)
	cc $(BUILD_FLAGS) $(HASHMAP_SUFF) $(ENV_SUFF) $(PARSER_SUFF) main.c \
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

