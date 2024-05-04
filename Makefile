# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 18:50:25 by bposa             #+#    #+#              #
#    Updated: 2024/05/04 18:44:53 by bposa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

SRCS	= 	push_swap.c \
			push_swap_utils.c \
			logic.c \
			init.c \
			input_validation.c \
			other_utils.c

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME)	: $(SRCS) libft/libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) libft/libft.a

libft/libft.a: libft/libft.h
	make -C libft/

clean:
	cd libft/ && make clean

fclean: clean
	rm -f $(NAME) libft/libft.a
	cd libft/ && make fclean

re: fclean all

.PHONY: all re clean fclean