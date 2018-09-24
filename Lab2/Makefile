PROJECT     = sort.out
CC          = gcc
CFLAGS      = -c -Wall -Wextra -Werror

.PHONY : all clean

all : $(PROJECT)

$(PROJECT) : insertion_sort.o main.o
	$(CC) $^ -o $@

main.o : main.c
	$(CC) $(CFLAGS) $^ -o $@

insertion_sort.o : insertion_sort.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o $(PROJECT)
