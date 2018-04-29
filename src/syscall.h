#include "types.h"

#define SYS_READ    0
#define SYS_WRITE   1
#define SYS_OPEN    2
#define SYS_CLOSE   3
#define SYS_STAT    4
#define SYS_FSTAT   5
#define SYS_MMAP    9
#define SYS_GETPID  39
#define SYS_GETDENTS    78
#define SYS_GETCWD  79
#define SYS_PTRACE  101
#define SYS_GETUID  102
#define SYS_GETGID  104
#define SYS_GETEUID 107
#define SYS_GETEGID 108
#define SYS_GETPPID 110
#define SYS_GETPGRP 111
#define SYS_GETDENTS64  217

intptr read(int fd, char *buf, uintptr nbytes);
intptr write(int fd, void const* data, uintptr nbytes);
intptr open3(const char *filename, intptr flags, intptr mode);
intptr open(const char *filename, intptr flags);
intptr close(int fd);
intptr getuid();

void* syscall5(
    void* number,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4,
    void* arg5
);

void* syscall4(
    void* number,
    void* arg1,
    void* arg2,
    void* arg3,
    void* arg4
);

void* syscall3(
    void* number,
    void* arg1,
    void* arg2,
    void* arg3
);

void* syscall2(
    void* number,
    void* arg1,
    void* arg2
);

void* syscall1(
    void* number,
    void* arg1
);

void* syscall(
    void* number
);
