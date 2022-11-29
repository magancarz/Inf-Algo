main: ex1.y ex1.l
	flex -o ex1l.c ex1.l
	bison -d -o ex1b.c ex1.y
	gcc -o ex1 ex1b.c ex1l.c
