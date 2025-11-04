CC = gcc

LDFLAGS = -lX11 -lXi -lcairo

program:
	$(CC) $(LDFLAGS) main.c -o program && ./program

clean:
	rm program
