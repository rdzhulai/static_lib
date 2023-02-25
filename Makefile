CC=gcc
CFLAGS=-Wall -Werror
LDLIB=-lmmath
OUTPUT=do_math

.PHONY:all

all:$(OUTPUT)
$(OUTPUT): main.c libmmath.a
	$(CC) $(CFLAGS) main.c -lmmath -o $@ -I ./include/ -L ./lib/
libmmath.a: add_numbers.o sub_numbers.o
	ar cr $@ $^
	mv $@ lib
add_numbers.o: add_numbers.c
	$(CC) $(CFLAGS) -c $^ -o $@
sub_numbers.o: sub_numbers.c
	$(CC) $(CFLAGS) -c $^ -o $@
clean:
	rm $(OUTPUT) *.o
push:
	astyle --mode=c --indent=spaces=4 *.c
	git commit -a
	git push
