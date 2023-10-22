CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=
SOURSES=s21_grep.c
OBJECTS=$(SOURSES:.c=.o)
EXECUTABLE=s21_grep

all: build

rebuild: clean build

build: s21_grep

clean:
	rm -rf *.o
	rm -rf ./s21_grep

s21_grep: s21_grep.o
	$(CC) *.o -o $(EXECUTABLE)

s21_grep.o: $(SOURSES)
	$(CC) $(CFLAGS) $(SOURSES)

check:
	cp ../../materials/linters/.clang-format ./
	clang-format -Werror -n ./*.c ./*.h
	rm -rf ./.clang-format

test: build
	bash test_for_grep.sh
	rm -rf log.txt