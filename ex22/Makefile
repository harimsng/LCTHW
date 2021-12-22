CC=gcc
CFLAGS=-g -DNDEBUG

NAME=ex22

SRC=ex22.c ex22_main.c

OBJ=$(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ): %.o: %.c 
	$(CC) $(CFLAGS) $< -c

clean:
	rm -f $(BIN)

.PHONY: all clean
