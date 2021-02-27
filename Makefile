p1: p1.o
	gcc -std=c11 -Wall -Wextra -O2 p1.o -lm -o p1

p1.o: p1.c
	gcc -c p1.c

clean: 
	rm *.o p1
