NAME = uls

INC = uls.h
OBJH = obj/uls.h

SRC = *.c

OBJ = *.o

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install clean

install:
	@make -sC libmx
	@cp $(addprefix src/, $(SRC)) .
	@cp $(addprefix inc/, $(INC)) .
	@clang $(CFLAGS) -c $(SRC) -I $(INC)
	@clang $(CFLAGS) libmx/libmx.a $(OBJ) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJ) ./obj
uninstall: clean
	@make uninstall -sC libmx
	@rm -rf $(NAME)
clean:
	@make clean -sC libmx
	@rm -rf $(INC) $(SRC) ./obj
reinstall: uninstall install
