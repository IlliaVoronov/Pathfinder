CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

INC = inc
LIB = libmx
OBJ = obj
SRC = src

SRCFILES := $(wildcard $(SRC)/*.c)
OBJFILES := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCFILES))
LIBMX = $(LIB)/libmx.a
OUTFILE = pathfinder

.PHONY: all install clean uninstall reinstall

all: install

install: $(LIBMX) $(OUTFILE)

$(LIBMX):
	make -C $(LIB)

$(OUTFILE): $(OBJFILES)
	$(CC) $(CFLAGS) -I$(INC) $^ $(LIBMX) -o $@

$(OBJFILES): $(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -I$(INC) -I$(LIB)/$(INC) -c $< -o $@

$(OBJ):
	mkdir -p $(OBJ)

uninstall: clean
	make -C $(LIB) uninstall
	rm -f $(OUTFILE)

clean:
	make -C $(LIB) clean
	rm -rf $(OBJ)

reinstall: uninstall all

