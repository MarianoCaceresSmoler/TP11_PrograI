program: main.o hardware.o
	 gcc main.o hardware.o -Wall -g -o program

main.o: main.c hardware.h
	 gcc -c main.c -Wall -g

hardware.o: hardware.c hardware.h
	 gcc -c hardware.c -Wall -g

clean:
	 rm -f *.o program
