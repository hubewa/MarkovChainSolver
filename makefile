CC = gcc
CFLAGS = -Wall -Werror -g

%.o: %.c
	$(CC) -c $<

main: main.o markov.o calc.o IO.o
	$(CC) -o $@ $^ -lm


#testCases: testCases.o markov.o calc.o IO.o
#	$(CC) -o $@ $^ -lm

main.o: main.c markov.h calc.h IO.h
#testCases.o: testCases.c markov.h calc.h IO.h
markov.o: markov.c markov.h
calc.o: calc.c markov.h calc.h
IO.o: IO.c markov.h IO.h

clean :
	rm -f main *.o core *.dSYM
#	rm -f testCases *.o core *.dSYM
