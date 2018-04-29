### This is a sample Makefile. You are free to modify this file.

TARGET  	= bin/elfluenza
LINK        = gcc
LFLAGS      = -m64 -Wl,-O1 -nostdlib

OBJECTS_DIR   = .obj/

SOURCES	=	src/virus.c src/syscall.c src/stdio.c

OBJECTS	=	.obj/virus.o .obj/syscall.o .obj/stdio.o

CFLAGS=-g -s -O2 -fPIC -pie -Wall -nostdlib -fno-unwind-tables -fno-asynchronous-unwind-tables -fomit-frame-pointer -fno-exceptions -fdata-sections -ffunction-sections -Wl,--gc-sections
#all: bin bin/virus
all: .obj bin $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(CFLAGS) src/stubstart.S src/syscall.S -o $(TARGET) $(OBJECTS)

#bin/virus: src/virus.c
#	$(CC) $(CFLAGS) src/stubstart.S -o$@ $<

.obj:
	@mkdir -p $@

.obj/virus.o: src/virus.c\
			src/stdio.h\
			src/elf.h\
			src/types.h\
			src/stat.h\
			src/fcntl.h\
			.obj/syscall.o\
			.obj/stdio.o
	$(CC) -c $(CFLAGS) -o$@ $<

.obj/stdio.o: src/stdio.c src/stdio.h
	$(CC) -c $(CFLAGS) -o$@ $<

.obj/syscall.o: src/syscall.c src/syscall.h\
			src/types.h
	$(CC) -c $(CFLAGS) -o$@ $<

bin:
	@mkdir -p $@

clean:
	@rm -rf bin/

.PHONY: all clean
