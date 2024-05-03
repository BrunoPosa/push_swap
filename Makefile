# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bposa <bposa@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 18:50:25 by bposa             #+#    #+#              #
#    Updated: 2024/05/03 15:28:37 by bposa            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= push_swap

SRCS	= push_swap.c

OBJCS	= $(SRCS:.c=.o)

DEPS	= 	push_swap.h \
			push_swap.c \
			push_swap_utils.c \
			logic.c \
			init.c \
			input_validation.c \
			other_utils.c

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

LIBNAME	= lib.a

LIBSRCS	= 	push_swap_utils.c \
			logic.c \
			init.c \
			input_validation.c \
			other_utils.c

LIBOBJCS	= $(LIBSRCS:.c=.o)

LIBDEPS	= 	libft/libft.h \
			libft/ft_atoi.c \
			libft/ft_bzero.c \
			libft/ft_calloc.c \
			libft/ft_isalnum.c \
			libft/ft_isalpha.c \
			libft/ft_isascii.c \
			libft/ft_isdigit.c \
			libft/ft_isprint.c \
			libft/ft_itoa.c \
			libft/ft_memchr.c \
			libft/ft_memcmp.c \
			libft/ft_memcpy.c \
			libft/ft_memmove.c \
			libft/ft_memset.c \
			libft/ft_putchar_fd.c \
			libft/ft_putendl_fd.c \
			libft/ft_putnbr_fd.c \
			libft/ft_putstr_fd.c \
			libft/ft_split.c \
			libft/ft_strchr.c \
			libft/ft_strdup.c \
			libft/ft_striteri.c \
			libft/ft_strjoin.c \
			libft/ft_strlcat.c \
			libft/ft_strlcpy.c \
			libft/ft_strlen.c \
			libft/ft_strmapi.c \
			libft/ft_strncmp.c \
			libft/ft_strnstr.c \
			libft/ft_strrchr.c \
			libft/ft_strtrim.c \
			libft/ft_substr.c \
			libft/ft_tolower.c \
			libft/ft_toupper.c \
			libft/ft_printf.c \
			libft/hex_prefix.c \
			libft/put_hex.c \
			libft/my_putnbr.c

all: $(NAME)

$(NAME)	: $(LIBNAME) libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBNAME) libft.a

$(LIBNAME): $(LIBOBJCS) $(DEPS)
	ar crs $(LIBNAME) $(LIBOBJCS)

libft.a: $(LIBDEPS)
	make -C libft/
	cd libft/ && cp libft.a ../

clean:
	rm -f $(OBJCS) $(LIBOBJCS)
	cd libft/ && make clean

fclean: clean
	rm -f $(NAME) $(LIBNAME) libft.a
	cd libft/ && make fclean

re: fclean all

.PHONY: all re clean fclean