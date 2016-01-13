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
myfs:$(LIB)
	gcc -o myfs main.c -lmyfs $(CFLAGS)
run:
	./myfs 
clean:
	rm $(OBJS) $(LIB) hw5 myshell.c~ myshell.h~ myfile.c~ myfile.h~ main.c~ Makefile~ kevin~
