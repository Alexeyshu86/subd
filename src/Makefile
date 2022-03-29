cc=gcc
flags=-Wall -Wextra -Werror -fsanitize=address
fileo=print_db.o

all: build

build: $(fileo)
	$(cc) $(flags) $(fileo) -o print_db.out

$(fileo): print_db.c
	$(cc) $(flags) -c print_db.c

run:
	./print_db.out

clean:
	rm *.o* 