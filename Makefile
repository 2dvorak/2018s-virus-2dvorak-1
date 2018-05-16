### This is a sample Makefile. You are free to modify this file.
CC = gcc
# removed -g, replaced -O2 with -Os, removed -fPIC, -pie
#CFLAGS=-s -Os -Wall -nostdlib -fPIC -pie -fno-unwind-tables -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-exceptions -fdata-sections -ffunction-sections -Wl,--gc-sections -fno-stack-protector -fmerge-all-constants -Wl,--build-id=none -fsingle-precision-constant -fno-math-errno -ldl -ffast-math -nostartfiles -fno-unroll-loops -Wl,-z,norelro
CFLAGS=-s -Wall -nostdlib -fPIC -pie

all: bin bin/elfluenza bin/victim bin/elfpacito

bin/elfluenza: src/virus.c
	$(CC) $(CFLAGS) src/stubstart.S src/syscall.S -o$@ $<

bin:
	@mkdir -p $@

bin/victim: src/victim.c
	$(CC) -o$@ $<

bin/elfpacito: src/elfpacito.c
	$(CC) $(CFLAGS) src/stubstart.S src/syscall.S -o$@ $<
	@echo $(shell echo -e '\x5a\xfe\xc0\xde') | dd of=bin/elfpacito bs=1 seek=10 conv=notrunc count=4 status=none

clean:
	@rm -rf bin/

.PHONY: all clean
