# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 18:50:25 by bposa             #+#    #+#              #
#    Updated: 2024/05/02 17:16:48 by bposa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

LIBNAME	= lib.a

CC	= cc

LIBSRCS	= 	push_swap_utils.c

LIBOBJCS	= $(LIBSRCS:.c=.o)

LIBDEPS	= 	libftprintf/libftprintf.h \
			libftprintf/*.c

SRCS	= 	push_swap.c \
			push_swap_utils.c \
			logic.c \
			init.c \
			input_validation.c \
			other_utils.c

DEPS	= push_swap.h

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME)	: $(LIBNAME)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBNAME) libftprintf.a

$(LIBNAME): libftprintf.a $(LIBOBJCS)
	ar crs $(LIBNAME) $(LIBOBJCS)

%.o: %.c  $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

libftprintf.a: $(LIBFTDEPS)
	make -C libftprintf/
	cd libftprintf/ && cp libftprintf.a ../

clean:
	rm -f $(OBJCS) $(LIBOBJCS)
	cd libftprintf/ && make clean

fclean: clean
	rm -f $(NAME) $(LIBNAME) libftprintf.a
	cd libftprintf/ && make fclean

re: fclean all

.PHONY: all re clean fclean