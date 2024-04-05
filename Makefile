##
## EPITECH PROJECT, 2023
## makefile
## File description:
## my own makefile
##

CC = gcc
NAME = mysh
SRCS = 	my_printf1.c	\
	my_printf2.c	\
	my_printf3.c	\
	my_printf4.c	\
	my_printf5.c	\
	my_printf0.c	\
	function_ls2.c	\
	function_ls3.c  \
	my_str_to_word_array.c
OBJS = $(SRCS:.c=.o)
autre = 	*~	\
		*.gcov	\
		*.gcno	\
		*gcda
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(SRCS) function_ls.c -o $(NAME) -g3

clean:
	rm -rf *.o

fclean: clean
	rm -rf *~ *# $(NAME) $(autre) unit_tests

re: fclean all

unit_tests: fclean $(NAME)
	$(CC) $(OBJS) tests/test/*.c -o unit_tests -coverage -lcriterion

tests_run: unit_tests
	./unit_tests
	gcovr
	gcovr --exclude tests/test/
	gcovr --exclude tests/test/ --branches
