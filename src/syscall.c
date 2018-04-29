#include "types.h"
#include "syscall.h"

//static
intptr read(int fd, char *buf, uintptr nbytes)
{
    return (intptr)
        syscall3(
            (void*)SYS_READ,
            (void*)(intptr)fd,
            (void*)buf,
            (void*)nbytes
        );
}

//static
intptr write(int fd, void const* data, uintptr nbytes)
{
    return (intptr)
        syscall3(
            (void*)SYS_WRITE,
            (void*)(intptr)fd,
            (void*)data,
            (void*)nbytes
        );
}

//static
intptr open3(const char *filename, intptr flags, intptr mode)
{
    return (intptr)
        syscall3(
            (void*)SYS_OPEN,
            (void*)filename,
            (void*)flags,
            (void*)mode
        );
}

intptr open(const char *filename, intptr flags)
{
    return (intptr)
        syscall2(
            (void*)SYS_OPEN,
            (void*)filename,
            (void*)flags
        );
}

intptr close(int fd)
{
    return (intptr)
        syscall1(
            (void*)SYS_CLOSE,
            (void*)(intptr)fd
        );
}

intptr getuid()
{
    return (intptr)
        syscall(
            (void*)SYS_GETUID
        );
}
