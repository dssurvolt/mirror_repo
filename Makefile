##
## EPITECH PROJECT, 2023
## epitech
## File description:
## desc
##

LIBNAME	=	108trigo

SRC	=	trigo1.c	\

OBJ	=	$(SRC:.c=.o)

autre 	= 	*~	\
		*.log	\
		a.out	\
		*.gcov	\
		*.gcno	\
		*.gcda

all	: 	$(LIBNAME)

$(LIBNAME):	$(OBJ)
		gcc $(SRC) trigo.c -o $(LIBNAME) -g3 -lm

clean:
		rm -f $(OBJ)
fclean:		clean
		rm -f $(LIBNAME) $(autre) 	unit_tests

re:		fclean all

unit_tests :	fclean $(LIBNAME)
	     	gcc $(SRC) tests/test/*.c -o unit_tests \
			-coverage -lcriterion -lgcov

tests_run :	unit_tests
		./unit_tests
		gcovr
		gcovr --exclude tests/test
		gcovr --exclude tests/test/ --branches
