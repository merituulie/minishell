# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmakinen <rmakinen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/07/20 08:05:08 by rmakinen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell
LIBFT_PATH = ./libft

BUILD_FLAGS = -Wall -Wextra -Werror -g -lreadline

HASHMAP_SRC = add_hashmap \
				clear_hashmap \
				utils_hashmap \

ENV_SRC = init \
		env

LEXER_SRC = lexer \
			lexer_utils \
			char_checks \
			syntax_error

COMMAND_SRC = init_command \
			command_utils \

PARSER_SRC = expand_env \
			parser_utils \
			concatenate \

H_FILES = hashmap \
		minishell \
		lexer \
		parsing \
		env \


BUILT_SRC = ft_pwd

HASHMAP_PRE = $(addprefix ./src/hashmap/, $(HASHMAP_SRC))
HASHMAP_SUFF = $(addsuffix .c, $(HASHMAP_PRE))
ENV_PRE = $(addprefix ./src/env/, $(ENV_SRC))
ENV_SUFF = $(addsuffix .c, $(ENV_PRE))
COMMAND_PRE = $(addprefix ./src/command/, $(COMMAND_SRC))
COMMAND_SUFF = $(addsuffix .c, $(COMMAND_PRE))
LEXER_PRE = $(addprefix ./src/lexer/, $(LEXER_SRC))
LEXER_SUFF = $(addsuffix .c, $(LEXER_PRE))
PARSER_PRE = $(addprefix ./src/parser/, $(PARSER_SRC))
PARSER_SUFF = $(addsuffix .c, $(PARSER_PRE))
HPRE = $(addprefix ./headers/, $(H_FILES))
HSUFF = $(addsuffix .h, $(HPRE))
BUILT_PRE = $(addprefix ./src/builtins/, $(BUILT_SRC))
BUILT_SUFF = $(addsuffix .c, $(BUILT_PRE))

.PHONY = all
all: $(NAME)

$(NAME):
	make -C $(LIBFT_PATH)
	cc $(BUILD_FLAGS) $(HASHMAP_SUFF) $(LEXER_SUFF) $(ENV_SUFF) $(COMMAND_SUFF) $(PARSER_SUFF) main.c \
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
