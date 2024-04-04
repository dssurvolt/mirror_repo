##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## a makefile to compile
##

NAME = libhashtable.a

SRCS =	$(wildcard src/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):$(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -r -f src/*.o

fclean: clean
	rm -rf src/*.a

re: fclean all
