TARGET = bin/atansi
FLAGS  = -std=c89 -Wall -Werror -Wextra

$(TARGET): src/atansi.c
	mkdir -p bin
	cc $(FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -fr bin/
	rm -fr pkg/
	.ypkg2/CLEANPKG

# For yports

installpkg2: buildpkg2
	ypkg2 install pkg/*

buildpkg2: $(TARGET)
	mkdir -p pkg
	.ypkg2/MAKEPKG
