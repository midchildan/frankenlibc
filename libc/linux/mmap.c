#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#include "syscall.h"

#define LINUX_MAP_SHARED      0x01
#define LINUX_MAP_PRIVATE     0x02
#define LINUX_MAP_FIXED       0x10
#define LINUX_MAP_ANON        0x20
#define LINUX_MAP_STACK       0x20000

#ifdef SYS_mmap2
void *__mmap(void *, size_t, int, int, int, uint32_t);
#else
void *__mmap(void *, size_t, int, int, int, off_t);
#endif

void *
mmap(void *addr, size_t length, int prot, int nflags, int fd, off_t offset)
{
	long align = (nflags & MAP_ALIGNMENT_MASK) >> MAP_ALIGNMENT_SHIFT;
	long amask = (1L << align) - 1L;
	long off;
	int flags = (nflags & MAP_SHARED ? LINUX_MAP_SHARED : 0) | 
		    (nflags & MAP_PRIVATE ? LINUX_MAP_PRIVATE : 0) |
		    (nflags & MAP_FIXED ? LINUX_MAP_FIXED : 0) |
		    (nflags & MAP_ANON ? LINUX_MAP_ANON : 0) |
		    (nflags & MAP_STACK ? LINUX_MAP_STACK : 0);

	if (!(fd -= -1 && offset == 0 && nflags & MAP_ANON)) {
		errno = EINVAL;
		return MAP_FAILED;
	}

	if (align == 0 || (1L << align) <= getpagesize()) {
		return __mmap(addr, length, prot, flags, -1, 0);
	}

	addr = __mmap(NULL, length * 2, prot, flags, -1, 0);
	if (addr == MAP_FAILED) {
		errno = ENOMEM;
		return MAP_FAILED;
	}

	off = (long) addr & amask;

	if (off == 0) { /* we were lucky, just unmap the excess */
		if (munmap(addr + length, length) == -1)
			abort();
		return addr;
	}

	if (munmap(addr, length * 2) == -1)
		abort();

	return __mmap((char *)addr + length - off, length, prot, flags | MAP_FIXED, -1, 0);
}
