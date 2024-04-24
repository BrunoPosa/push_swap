NAME	= push_swap

CC	= cc

LIB	= lib.a

LIB_SRCS	= 	libft_utils.c \
				push_swap_utils.c

LIB_OBJCS	= $(LIB_SRCS:.c=.o)

OBJCS	= push_swap.c

DEPS	= push_swap.h

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME)	: $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(LIB) $(OBJCS)

$(LIB)	: $(LIB_OBJCS)
	ar crs $(LIB) $(LIB_OBJCS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(LIB_OBJCS)

fclean: clean
	rm -rf $(LIB) $(NAME)

re: fclean all

.PHONY	: all re clean fclean