TARGET = bin/atansi
SRC    = src/atansi.c
FLAGS  = -Wall -Werror -Wextra

$(TARGET): $(SRC)
	gcc $^ -o $@

.PHONY: clean

clean:
	rm -f bin/*
