### This is a sample Makefile. You are free to modify this file.
CC = gcc
# removed -g, replaced -O2 with -Os, removed -fPIC, -pie
CFLAGS=-s -Os -Wall -nostdlib -fno-unwind-tables -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-exceptions -fdata-sections -ffunction-sections -Wl,--gc-sections -fno-stack-protector -fmerge-all-constants -Wl,--build-id=none -fsingle-precision-constant -fno-math-errno -ldl -ffast-math -nostartfiles -fno-unroll-loops -Wl,-z,norelro
all: bin bin/virus

bin/virus: src/virus.c
	$(CC) $(CFLAGS) src/stubstart.S src/syscall.S -o$@ $<

bin:
	@mkdir -p $@

clean:
	@rm -rf bin/

.PHONY: all clean
