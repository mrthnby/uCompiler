CC = gcc
CFLAGS = -Wall
OUT = uCompiler
FILES = src/main.c src/converter.c

all:
	$(CC) $(CFLAGS) $(FILES) -o $(OUT)

exec:
	./uCompiler

clean:
	rm uCompiler