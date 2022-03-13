GCC = gcc
G++ = g++
FLAGS = -pedantic -Wall
PROGS = Bench01 benchReference MMc01

Bench01: 
	$(G++) $(FLAGS) $@.cpp -c
	$(G++) $(FLAGS) $@.o -o $@

benchReference: 
	$(G++) $(FLAGS) $@.cpp -c
	$(G++) $(FLAGS) $@.o -o $@

MMc01:
	$(GCC) $(FLAGS) $@.c -c
	$(GCC) $(FLAGS) $@.o -o $@

clean:
	$(RM) $(PROGS) *.o
