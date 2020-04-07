sshell: main.o reader.o
	gcc -g -ansi -Wall main.o reader.o -lm -pedantic -o sshell

main.o: main.c shell.h
	gcc -c -g -ansi main.c -lm -Wall -pedantic -o main.o 

reader.o: reader.c shell.h
	gcc -c -g -ansi reader.c -lm -Wall -pedantic -o reader.o 