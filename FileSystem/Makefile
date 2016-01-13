CFLAGS = -L. 
LIB = libmyfs.a
OBJS = myfile.o myshell.o

$(LIB):$(OBJS)
	@ar rcs $(LIB) $(OBJS)
lib:$(LIB)

myfile.o:myfile.c myfile.h
	gcc -c myfile.c
myshell.o:myshell.c myshell.h
	gcc -c  myshell.c

hw5:$(LIB)
	gcc -o hw5 main.c -lmyfs $(CFLAGS)

run:
	hw5 
clean:
	rm $(OBJS) $(LIB) hw5 myshell.c~ myshell.h~ myfile.c~ myfile.h~ main.c~ Makefile~ kevin~
