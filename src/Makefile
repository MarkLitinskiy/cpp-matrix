CC = gcc -std=c++17 -g
FLAGS = -Wall -Werror -Wextra
OS = $(shell uname)
LIBSOURCES = s21_matrix_oop.cc my_own_tests.cc

ifeq ($(OS), Linux)
	CHECKFLAGS=-lgtest -lgtest_main -lrt -lm -lstdc++ -pthread -fprofile-arcs -ftest-coverage
else
	CHECKFLAGS=-lgtest -lgtest_main -lm -lpthread -fprofile-arcs -ftest-coverage -lstdc++
endif

all: test
	
s21_matrix_oop.a:
	$(CC) $(FLAGS) -c s21_matrix_oop.cc
	ar -crs lib_s21_matrix_oop.a s21_matrix_oop.o
	rm -f *.o

test: clean
	$(CC) $(FLAGS) $(LIBSOURCES) -o run $(CHECKFLAGS) -lgcov --coverage
	./run

gcov_report: test
	lcov -t "gcov_report" --ignore-errors mismatch -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

test_leaks: test
	leaks --atExit -- ./run

valgrind: test
	 CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./run
	 make clean

docker_check:
	docker build -t "valgrind:1.0" .
	docker run --rm -v $PWD:/tmp -w /tmp valgrind:1.0

to_style:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./*.cc
	clang-format -i ./*.h
	rm -rf .clang-format

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -style=Google -n s21_matrix_oop.* my_own_tests.cc
	rm -rf .clang-format

clean:
	rm -rf report \
	lib_s21_matrix_oop.a \
	report.info \
	*.gcda \
	*.gcno \
	s21_matrix_oop.o \
	run.dSYM \
	run