FLAGS  = -Wall -Werror -Wextra

bin/atansi: src/atansi.c
	mkdir -p bin
	gcc $^ -o $@

.PHONY: clean

clean:
	rm -f bin/*
