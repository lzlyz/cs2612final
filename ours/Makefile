lexer.h: lang.l
	flex lang.l

lexer.c: lang.l
	flex lang.l

parser.c: lang.y
	bison -o parser.c -d -v lang.y

parser.h: lang.y
	bison -o parser.c -d -v lang.y

dictionary.o: dictionary.c dictionary.h
	gcc -c dictionary.c

lang.o: lang.c lang.h dictionary.h
	gcc -c lang.c

parser.o: parser.c parser.h lexer.h lang.h
	gcc -c parser.c

lexer.o: lexer.c lexer.h parser.h lang.h
	gcc -c lexer.c

main.o: main.c lexer.h parser.h lang.h
	gcc -c main.c

main: lang.o parser.o lexer.o dictionary.o main.o
	gcc lang.o parser.o lexer.o dictionary.o main.o -o main

all: main

clean:
	rm lexer.h
	rm lexer.c 
	rm parser.h 
	rm parser.c
	rm lang.o 
	rm lexer.o
	rm main.o
	rm parser.o 
	rm main

%.c: %.y

%.c: %.l

.DEFAULT_GOAL := all

