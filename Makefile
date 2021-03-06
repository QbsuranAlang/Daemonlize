
CC=gcc
TARGETS = daemonlize

all: $(TARGETS)

daemonlize: daemonlize.o
	$(CC) $^ -o $@

daemonlize.o: daemonlize.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f daemonlize.o
	rm -f $(TARGETS)
