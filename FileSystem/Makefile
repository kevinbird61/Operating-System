hw5:main.o myfile.o myshell.o
	gcc -o hw5 main.o myfile.o myshell.o
main.o:main.c myshell.h
	gcc -c main.c
myfile.o:myfile.c myfile.h
	gcc -c myfile.c
myshell.o:myshell.c myshell.h
	gcc -c  myshell.c

run:
	./hw5 
clean:
	rm main.o myfile.o myshell.o hw5 myshell.c~ myshell.h~ myfile.c~ myfile.h~ main.c~ Makefile~
