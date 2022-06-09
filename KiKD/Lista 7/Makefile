# Makefile

all: encode noise decode check clean

encode: encode.o
	g++ -o encode encode.o

noise: noise.o
	g++ -o noise noise.o

decode: decode.o
	g++ -o decode decode.o

check: check.o
	g++ -o check check.o

clean:
	rm -f *.o
