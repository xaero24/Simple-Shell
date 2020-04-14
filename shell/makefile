sshell: main.o reader.o parsing.o utilities.o 
	gcc -g -ansi -Wall main.o reader.o parsing.o utilities.o -lm -pedantic -o sshell

main.o: hw2.c shell.h
	gcc -c -g -ansi hw2.c -lm -Wall -pedantic -o main.o 

reader.o: reader.c shell.h
	gcc -c -g -ansi reader.c -lm -Wall -pedantic -o reader.o 

parsing.o: parsing.c shell.h
	gcc -c -g -ansi parsing.c -lm -Wall -pedantic -o parsing.o 

utilities.o: utilities.c shell.h
	gcc -c -g -ansi utilities.c -lm -Wall -pedantic -o utilities.o 