# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2023/08/16 11:45:57 by yoonslee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell
LIBFT_PATH = ./libft

BUILD_FLAGS = -Wall -Wextra -g -lreadline -Werror #-fsanitize=address,undefined

HASHMAP_SRC = add_hashmap \
				clear_hashmap \
				utils_hashmap \

ENV_SRC = init_env \
			env

COMMON_SRC =	file_checker \
				file \
				pipe \
				redirection \
				save_exit_status \
				signal \
				pid \
				shlvl \
				executer \
				free

LEXER_SRC = lexer \
			lexer_utils \
			char_checks \
			syntax_error \
			add_lines_lexer

COMMAND_SRC = init_command \
			redir_command \
			add_command \
			input_command \
			full_command \
			flags_command \
			heredoc_command

PARSER_SRC = expand_env \
			parser_utils \
			concatenate \
			parser_special

BUILTIN_SRC = export \
			echo \
			cd \
			heredoc \
			pwd \
			execve \
			unset \
			exit \

H_FILES = hashmap \
		minishell \
		lexer \
		parsing \


HASHMAP_PRE = $(addprefix ./src/hashmap/, $(HASHMAP_SRC))
HASHMAP_SUFF = $(addsuffix .c, $(HASHMAP_PRE))
ENV_PRE = $(addprefix ./src/env/, $(ENV_SRC))
ENV_SUFF = $(addsuffix .c, $(ENV_PRE))
COMMON_PRE = $(addprefix ./src/common/, $(COMMON_SRC))
COMMON_SUFF = $(addsuffix .c, $(COMMON_PRE))
COMMAND_PRE = $(addprefix ./src/command/, $(COMMAND_SRC))
COMMAND_SUFF = $(addsuffix .c, $(COMMAND_PRE))
LEXER_PRE = $(addprefix ./src/lexer/, $(LEXER_SRC))
LEXER_SUFF = $(addsuffix .c, $(LEXER_PRE))
PARSER_PRE = $(addprefix ./src/parser/, $(PARSER_SRC))
PARSER_SUFF = $(addsuffix .c, $(PARSER_PRE))
BUILTIN_PRE = $(addprefix ./src/builtins/, $(BUILTIN_SRC))
BUILTIN_SUFF = $(addsuffix .c, $(BUILTIN_PRE))
HPRE = $(addprefix ./headers/, $(H_FILES))
HSUFF = $(addsuffix .h, $(HPRE))

.PHONY = all
all: $(NAME)

$(NAME):
	make -C $(LIBFT_PATH)
	cc -L  ~/.brew/opt/readline/lib -I  ~/.brew/opt/readline/include $(BUILD_FLAGS) $(HASHMAP_SUFF) $(LEXER_SUFF) $(ENV_SUFF) $(COMMON_SUFF) \
	$(COMMAND_SUFF) $(PARSER_SUFF) $(BUILTIN_SUFF) main.c \
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
