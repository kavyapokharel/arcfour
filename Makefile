CFLAGS ?= -O2 -Wall -Wextra

.PHONY: all arcfour clean
all: arcfour example

arcfour: arcfour.so

arcfour.so: arcfour.o
	$(CC) $(LDFLAGS) -shared -o $@ $^

example: arcfour.o example.o
	$(CC) $(LDFLAGS) -o $@ $^

arcfour.o: arcfour.c arcfour.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@

example.o: example.c arcfour.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) arcfour.o example.o arcfour.so example
