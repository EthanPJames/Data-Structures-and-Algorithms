
pa4:
	gcc -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic *.c -o pa4

pa4_debug:
	gcc -g -std=c99 -Wall -Wshadow -Wvla -pedantic *.c -o pa4

test_1:
	./pa4 infile out_file

	diff out_file expected