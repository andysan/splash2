/*
 * Copyright (c) 1990, 1991, 1992 Sam Leffler
 * Copyright (c) 1991, 1992 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF 
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 */

#ifndef _COMPAT_
#define	_COMPAT_
/*
 * This file contains a hodgepodge of definitions and
 * declarations that are needed to provide compatibility
 * between the native system and the base UNIX implementation
 * that the library assumes (~4BSD).  In particular, you
 * can override the standard i/o interface (read/write/lseek)
 * by redefining the ReadOK/WriteOK/SeekOK macros to your
 * liking.
 *
 * NB: This file is a mess.
 */

#define	USE_PROTOTYPES	1
#define	USE_CONST	1

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*
 * Workarounds for BSD lseek definitions.
 */
#if defined(SYSV) || defined(VMS)
#if defined(SYSV)
#include <unistd.h>
#endif
#define	L_SET	SEEK_SET
#define	L_INCR	SEEK_CUR
#define	L_XTND	SEEK_END
#endif
#ifndef L_SET
#define L_SET	0
#define L_INCR	1
#define L_XTND	2
#endif

/*
 * Return an open file descriptor or -1.
 */
#define	TIFFOpenFile(name, mode, prot)	open(name, mode, prot)

/*
 * Return the size in bytes of the file
 * associated with the supplied file descriptor.
 */
extern	long TIFFGetFileSize(int fd);

#ifdef MMAP_SUPPORT
/*
 * Mapped file support.
 *
 * TIFFMapFileContents must map the entire file into
 *     memory and return the address of the mapped
 *     region and the size of the mapped region.
 * TIFFUnmapFileContents does the inverse operation.
 */
extern	int TIFFMapFileContents(int fd, char **paddr, long *psize);
extern	void TIFFUnmapFileContents(char *addr, long size);
#endif

/*
 * Default Read/Seek/Write definitions.
 */
#ifndef ReadOK
#define	ReadOK(fd, buf, size)	(read(fd, (char *)buf, size) == size)
#endif
#ifndef SeekOK
#define	SeekOK(fd, off)	(lseek(fd, (long)off, L_SET) == (long)off)
#endif
#ifndef WriteOK
#define	WriteOK(fd, buf, size)	(write(fd, (char *)buf, size) == size)
#endif

/*
 * dblparam_t is the type that a double precision
 * floating point value will have on the parameter
 * stack (when coerced by the compiler).
 */
typedef double dblparam_t;

/*
 * Varargs parameter list handling...YECH!!!!
 */
#define	USE_VARARGS	0

#include <stdarg.h>
#define	VA_START(ap, parmN)	va_start(ap, parmN)

#endif /* _COMPAT_ */
