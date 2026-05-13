CC=gcc
CFLAGS=-Wall -Wextra -Iinclude
AR=ar
ARFLAGS=rcs

SRC=src/app.c \
    src/router.c \
    src/request.c \
    src/response.c \
    src/server.c

OBJ=$(SRC:.c=.o)

LIB=liblitehttp.a
EXAMPLE_BIN=example_app

all: lib example

lib: $(LIB)

$(LIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

example: lib examples/main.c
	$(CC) $(CFLAGS) examples/main.c -L. -llitehttp -o $(EXAMPLE_BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB) $(EXAMPLE_BIN) app

.PHONY: all lib example clean