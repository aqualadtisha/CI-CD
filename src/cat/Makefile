CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=
SOURSES=s21_cat.c
OBJECTS=$(SOURSES:.c=.o)
EXECUTABLE=s21_cat

all: build

rebuild: clean build

build: s21_cat

clean:
	rm -f *.o
	rm -f ./s21_cat

s21_cat: s21_cat.o
	$(CC) *.o -o $(EXECUTABLE)

s21_cat.o: $(SOURSES)
	$(CC) $(CFLAGS) $(SOURSES)

check:
	cp ../../materials/linters/.clang-format ./
	clang-format -Werror -n ./*.c ./*.h
	rm -f ./.clang-format

test: build
	bash test_for_cat.sh
	rm -f log.txt