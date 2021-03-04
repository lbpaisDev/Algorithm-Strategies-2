
p1: p1.c
	gcc -std=c11 -g -Wall -Wextra -O0 "p1.c" -lm -o p1

clean: 
	rm p1
