p1: p1.o
	gcc-8 -std=c11 -Wall -Wextra -O2 p1.o -lm -o p1

p1.o: p1.c
	gcc-8 -c p1.c

clean: 
	rm *.o p1
