
p1: p1v2.c
	gcc-8 -std=c11 -g -Wall -Wextra -O0 "p1v2.c" -lm -o p1

clean: 
	rm p1
