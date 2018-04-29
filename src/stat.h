/*
 * POSIX Extensions
 */
typedef	unsigned char	uchar_t;
typedef	unsigned short	ushort_t;
typedef	unsigned int	uint_t;
typedef	unsigned long	ulong_t;

typedef	long long		longlong_t;
typedef	unsigned long long	u_longlong_t;

typedef ulong_t	dev_t;
typedef ulong_t		ino_t;

// ???
#if defined(_LP64) || defined(_I32LPx)
typedef	uint_t	mode_t;			/* file attribute type	*/
typedef	uint_t nlink_t;			/* file link type	*/
typedef int	pid_t;			/* process id type	*/
typedef	int	uid_t;
#else
typedef	ulong_t	mode_t;			/* (historical version) */
typedef	ulong_t	nlink_t;		/* (historical version) */
typedef	long	pid_t;			/* (historical version) */
typedef	long	uid_t;
#endif

typedef	uid_t	gid_t;

typedef longlong_t	off_t;

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
	ulong_t	st_flags;		/* user defined flags for file */
	ulong_t	st_gen;			/* file generation number */
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

#define	S_IFMT	 0170000		/* type of file */
#define	S_IFIFO	 0010000		/* named pipe (fifo) */
#define	S_IFCHR	 0020000		/* character special */
#define	S_IFDIR	 0040000		/* directory */
#define	S_IFBLK	 0060000		/* block special */
#define	S_IFREG	 0100000		/* regular */
#define	S_IFLNK	 0120000		/* symbolic link */
#define	S_IFSOCK 0140000		/* socket */

#define	S_ISVTX	 0001000		/* save swapped text even after use */

#define S_BLKSIZE	512		/* block size used in the stat struct */
