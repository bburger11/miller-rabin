CC     = gcc
CFLAGS = -std=gnu99 -Wall

.PHONY: all clean

all: miller-rabin

miller-rabin: miller-rabin.c
	@echo "Compiling $@..."
	@$(CC) $(CFLAGS) $^ -o $@

clean:
	@echo "Cleaning..."
	@rm -f miller-rabin
