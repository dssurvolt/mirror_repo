##
## EPITECH PROJECT, 2025
## Day05
## File description:
## Makefile
##

PROJECT = { RAFAREN }

BINARY	=	arcade

SRC	=	src/core_program/core.cpp	\
		src/arcade.cpp	\

SRC_PACMAN	=	src/games_libraries/pac-man/pac-man.cpp	\
	src/games_libraries/pac-man/a_star/path_finding.cpp	\
	src/games_libraries/pac-man/loading_maze.cpp	\
				src/arcade.cpp	\

SRC_SNAKE	=	src/games_libraries/snake/snake.cpp	\
				src/arcade.cpp	\

SRC_NIBBLER	=	src/games_libraries/nibbler/nibbler.cpp	\
				src/arcade.cpp	\

SRC_NCURSES	=	src/graphics_libraries/ncurses/ncurses.cpp	\
				src/arcade.cpp	\

SRC_SFML	=	src/graphics_libraries/sfml/sfml.cpp	\
				src/arcade.cpp	\

SRC_SDL2	=	src/graphics_libraries/sdl2/sdl2.cpp	\
				src/arcade.cpp	\

SRC_CORE	=	src/core_program/core.cpp	\

SRCTEST	=	

MAIN	=	src/main.cpp

EXCLUDE_TEST	=	tests/

TEST =	

autre 	= 	*~	\
		*.log	\
		a.out	\
		*.gcov	\
		*.gcno	\
		*.gcda	\
		*.o	\
		*.d	\
		$(BINARY)

ERROR	=	-Wall -Wextra -Werror

VALGRIND	=	-g3

PROFILER	=	-pg

NCURSES	=	-lncurses

RECOMPILE	=	-MMD -MP

SFML	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SDL2	=	-lSDL2 -lSDL2_image -ldl -fno-gnu-unique

STD_VERSION	=	-std=c++20


FLAGS	=	$(VALGRIND) $(STD_VERSION) $(ERROR) $(SFML) $(SDL2) $(NCURSES)

all	:	games	graphicals	core

games	:
		@echo "\033[32m=== CLEAN REPOSITORY ===\033[0m"
	g++ -shared -o lib/arcade_pacman.so $(SRC_PACMAN) $(NCURSES) $(SFML) $(SDL2) -fPIC
		@echo "\033[32m=== CLEAN REPOSITORY ===\033[0m"
	g++ -shared -o lib/arcade_snake.so $(SRC_SNAKE) $(NCURSES) $(SFML) $(SDL2) -fPIC
		@echo "\033[32m=== CLEAN REPOSITORY ===\033[0m"
	g++ -shared -o lib/arcade_nibbler.so $(SRC_NIBBLER) $(NCURSES) $(SFML) $(SDL2) -fPIC

graphicals	:
		@echo "\033[32m=== NCURSES ===\033[0m"
	g++ -shared -o lib/arcade_ncurses.so $(SRC_NCURSES) $(FLAGS) -fPIC
		@echo "\033[32m=== SFML ===\033[0m"
	g++ -shared -o lib/arcade_sfml.so $(SRC_SFML) $(SFML) -fPIC
		@echo "\033[32m=== SDL2 ===\033[0m"
	g++ -shared -o lib/arcade_sdl2.so $(SRC_SDL2) $(SDL2) -fPIC

core	:
		@echo "\033[32m=== CORE ===\033[0m"
	g++ $(SRC) $(VALGRIND) $(SFML) $(SDL2) $(NCURSES) $(MAIN) -o $(BINARY)


clean	:
		@echo "\033[33m=== $(PROJECT) ===\033[0m"
		@echo "\033[32m=== CLEAN REPOSITORY ===\033[0m"
		rm -f $(OBJ)
		@echo "\033[31m===        END        ===\033[0m"
fclean	:	clean
		@echo "\033[33m=== $(PROJECT) ===\033[0m"
		@echo "\033[32m=== FCLEAN REPOSITORY ===\033[0m"
		rm -f $(autre) 	unit_tests $(LIBNAME)
		@echo "\033[31m===        END        ===\033[0m"

re:		fclean	all

unit_tests	:	fclean clean
			@echo "\033[33m=== $(PROJECT) ===\033[0m"
			@echo "\033[32m=== START UNIT_TEST ===\033[0m"
			g++ $(SRCTEST) $(TEST) -o unit_tests\
			-coverage -lcriterion -lgcov
			@echo "\033[32m=== END UNIT_TEST ===\033[0m"

tests_run :	unit_tests
		@echo "\033[34m=== START TESTS RUN ===\033[0m"
		./unit_tests
		@echo "\033[32m=== END TESTS RUN ===\033[0m"
		@echo "\033[34m=== START GCOVR ===\033[0m"
		gcovr
		@echo "\033[32m=== END GCOVR ===\033[0m"
		@echo "\033[34m=== START GCOVR --EXCLUDE ===\033[0m"
		gcovr --exclude $(EXCLUDE_TEST)
		@echo "\033[32m=== END GCOVR --EXCLUDE ===\033[0m"
		@echo "\033[34m=== START GCOVR --EXCLUDE --BRANCHES ===\033[0m"
		gcovr --exclude $(EXCLUDE_TEST) --branches
		@echo "\033[32m=== END GCOVR --EXCLUDE --BRANCHES ===\033[0m"
