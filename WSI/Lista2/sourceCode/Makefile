SOURCES = $(wildcard *.c)
BINARY = $(patsubst %.c, %, $(SOURCES))

FLAGS = -W -pedantic -std=c++17 -O3
.PHONY = all clean

all: $(BINARY)

$(BINARY): %: %.c
	g++ $(FLAGS) $^ -o $@
	strip $@

clean:
	rm -f $(BINARY)

