##
## EPITECH PROJECT, 2025
## Zappy
## File description:
## Zappy
##

TESTS	=

RM	=	rm -rf

unit_tests: tests/test.cpp $(TESTS)
	@echo "Compiling unit_tests..."
	@g++ -o unit_tests tests/test.cpp $(TESTS) -lcriterion --coverage

tests_run: unit_tests
	@echo "Running unit_tests..."
	@./unit_tests
	@gcovr --exclude unit_tests/ --branches
	@gcovr --exclude unit_tests/

clean:
	@echo "clean up undesirable file..."
	@$(RM) *~ *# *.log *.a *.out *.gcno *gcda *unit_tests

fclean: clean
	@echo "clean up..."
	@$(RM) $(SERVERBINARY) $(AIBINARY) $(GUIBINARY)

re: fclean all
