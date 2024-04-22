##
## Makefile 
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -g -std=c99 -Wall -Wshadow -Wvla -pedantic

## if you want to compile with the -O3 flag, comment the preceding CFLAGS and 
## uncomment the following CFLAGS

# CFLAGS	= -std=c99 -Wall -Wshadow -Werror -Wvla -O3 -pedantic -fstack-protector-strong --param ssp-buffer-size=1

## Build rule to build executable, by default, pe01 is build since it 
## is the label of the first rule

pa1: sequence.o shell_array.o shell_list.o pa1.o
	$(CC) $(CFLAGS) sequence.c shell_array.c shell_list.c pa1.c -o pa1

## rule to test with argument option 0


## rule to test with argument option 1



##memory: pe09
##	valgrind --log-file=log0.txt ./pe099 0 inputfile
##	valgrind --log-file=log1.txt ./pe01 1 inputfile

## rule to clean up object files and executable so that you can rebuild

clean:	
	rm -f sequence.o shell_array.o shell_list.o pa1.o pa1

## rule to compile .c to .o

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
