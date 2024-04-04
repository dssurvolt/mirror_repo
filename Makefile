##
## EPITECH PROJECT, 2023
## makefile
## File description:
## my own makefile
##
CC = gcc
NAME = my_ls
SRCS =	my_printf1.c	\
	my_printf2.c	\
	my_printf3.c	\
	my_printf4.c	\
	my_printf5.c	\
	my_printf0.c	\
	function_ls.c	\
	function_ls2.c	\
	function_ls3.c  \
	my_str_to_word_array.c
OBJS = $(SRCS:.c=.o)
all:$(OBJS)
	$(CC) $(SRCS) -o $(NAME)
clean :
	rm -rf *.o
fclean: clean
	rm -rf my_ls
re: fclean all
