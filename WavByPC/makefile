
cf = test.o wav.o
option = -std=c99
optimize = -O0

.PHONY:all
all: a.out

a.out: $(cf)
	$(CC) -Wall $(optimize) $(option) $(cf)  
wav.o: wav.c
	gcc -c $<
wav.o: wav.h
.PHONY:clean
clean:
	$(RM) a.out $(cf) 

#.PHONY:all
#all: a.out
#
#a.out: test.o wav.o
#	gcc -Wall  test.o wav.o
#wav.o: wav.c
#	gcc -c wav.c
#.PHONY:clean
#clean:
#	rm -f a.out test.o wav.
