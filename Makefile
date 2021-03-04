
p1: p1.c
	gcc-8 -std=c11 -g -Wall -Wextra -O2 "p1.c" -lm -o p1

clean: 
	rm p1
