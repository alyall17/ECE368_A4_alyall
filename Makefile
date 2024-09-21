WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

SRCS = main.c
OBJS = $(SRCS:%.c=%.o)

# diff -w means do not care about space

a4: $(OBJS) 
	$(GCC) $(OBJS) -o a4

.c.o: 
	$(GCC) -c $*.c

run: a4
	./a4

clean: # remove all machine generated files
	rm -f a4 *.o output* *~