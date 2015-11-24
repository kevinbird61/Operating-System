Hw3: Hw3.o fetchString.o
	gcc -o Hw3 Hw3.o fetchString.o
Hw3.o : Hw3.c fetchString.h
	gcc -c Hw3.c
fetchString.o : fetchString.c fetchString.h
	gcc -c fetchString.c

run:
	./Hw3 input.txt "oslab2015" 3

