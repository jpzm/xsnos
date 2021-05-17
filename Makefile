CC := cc

all: linux

linux:
	${CC} -Wall -ggdb xsnos.c main.c -o xsnos

clean:
	rm -f xsnos
