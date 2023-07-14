# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoonslee <yoonslee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/17 14:59:05 by yoonslee          #+#    #+#              #
#    Updated: 2023/03/08 10:27:47 by yoonslee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex

SRCS = pipex.c error_msg.c children_process.c free_close.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME):$(OBJS)
	make -C libft all
	cc $(FLAGS) $(OBJS) libft/libft.a -o $(NAME)

$(OBJS):$(SRCS)
	cc -c $(FLAGS) $(SRCS)

clean:
	rm -rf $(OBJS)
	make -C libft clean

fclean:clean
	rm -rf $(NAME)
	rm -rf libft/libft.a

re: fclean clean all

.PHONY: all clean fclean re