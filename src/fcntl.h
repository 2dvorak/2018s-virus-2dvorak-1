/*
 * File status flags: these are used by open(2), fcntl(2).
 * They are also used (indirectly) in the kernel file structure f_flags,
 * which is a superset of the open/fcntl flags.  Open flags and f_flags
 * are inter-convertible using OFLAGS(fflags) and FFLAGS(oflags).
 * Open/fcntl flags begin with O_; kernel-internal flags begin with F.
 */
/* open-only flags */
#define	O_RDONLY	0x0000		/* open for reading only */
#define	O_WRONLY	0x0001		/* open for writing only */
#define	O_RDWR		0x0002		/* open for reading and writing */
#define	O_ACCMODE	0x0003		/* mask for above modes */


/*
 * Kernel encoding of open mode; separate read and write bits
 * that are independently testable: 1 greater than the above.
 */
#define	FREAD		0x0001
#define	FWRITE		0x0002

#define	O_NONBLOCK	0x0004		/* no delay */
#define	O_APPEND	0x0008		/* set append mode */

#define	O_SHLOCK	0x0010		/* open with shared file lock */
#define	O_EXLOCK	0x0020		/* open with exclusive file lock */
#define	O_ASYNC		0x0040		/* signal pgrp when data ready */
#define	O_FSYNC		0x0080		/* synchronous writes */

#define	O_CREAT		0x0200		/* create if nonexistant */
#define	O_TRUNC		0x0400		/* truncate to zero length */
#define	O_EXCL		0x0800		/* error if already exists */

#define	FMARK		0x1000		/* mark during gc() */
#define	FDEFER		0x2000		/* defer for next gc pass */
#define	FHASLOCK	0x4000		/* descriptor holds advisory lock */