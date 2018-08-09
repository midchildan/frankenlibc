COMPILE.c?=$(CC) -c $(CPPFLAGS) $(CFLAGS)
COMPILE.cc?=$(CXX) -c $(CPPFLAGS) $(CXXFLAGS)
COMPILE.S?=$(CC) -c $(CPPFLAGS) $(ASFLAGS)
MAKE?=make
INSTALL?=install
RUMPOBJ?=../../rumpobj
OBJDIR=$(RUMPOBJ)/platform
RUMP?=$(RUMPOBJ)/rump
CIRCLE_DIR?=$(RUMPOBJ)/circle
CRTDIR=$(RUMP)/lib
CRTFILES=$(CRTDIR)/startup.o $(CRTDIR)/crt0.o
CRTFILES+=$(CRTDIR)/crti.o $(CRTDIR)/crtn.o
CRTFILES+=$(CRTDIR)/crtbegin.o $(CRTDIR)/crtbeginT.o
CRTFILES+=$(CRTDIR)/crtend.o
OBJ=$(CRTFILES)
LIBG=$(CRTDIR)/libg.a
OBJ+=$(LIBG)
OBJ+=$(OBJDIR)/clock_getres.o
OBJ+=$(OBJDIR)/clock_gettime.o
OBJ+=$(OBJDIR)/clock_nanosleep.o
OBJ+=$(OBJDIR)/_exit.o
OBJ+=$(OBJDIR)/fcntl.o
OBJ+=$(OBJDIR)/fstat.o
OBJ+=$(OBJDIR)/fsync.o
OBJ+=$(OBJDIR)/getpagesize.o
OBJ+=$(OBJDIR)/getrandom.o
OBJ+=$(OBJDIR)/kill.o
OBJ+=$(OBJDIR)/lseek.o
OBJ+=$(OBJDIR)/mmap.o
OBJ+=$(OBJDIR)/mprotect.o
OBJ+=$(OBJDIR)/__libc_start_main.o
OBJ+=$(OBJDIR)/poll.o
OBJ+=$(OBJDIR)/pread.o
OBJ+=$(OBJDIR)/pwrite.o
OBJ+=$(OBJDIR)/preadv.o
OBJ+=$(OBJDIR)/pwritev.o
OBJ+=$(OBJDIR)/read.o
OBJ+=$(OBJDIR)/readv.o
OBJ+=$(OBJDIR)/write.o
OBJ+=$(OBJDIR)/writev.o
OBJ+=$(CIRCLE_DIR)/libcircle.a
OBJ+=$(CIRCLE_DIR)/libcircle_net.a
OBJ+=$(CIRCLE_DIR)/libcircle_usb.a
HEADERS=$(CRTDIR) $(OBJDIR) $(CIRCLE_DIR)
INCLUDES=-I../include -I../../franken/include -I -I. -I./circle/include
CPPFLAGS+=-nostdinc $(INCLUDES)
CFLAGS+=-fno-stack-protector
CXXFLAGS+=-fno-stack-protector
RANLIB?=ranlib
CIRCLE_FLAGS?=RASPPI=2 FLOAT_ABI=softfp STDLIB_SUPPORT=2 ARCH=

default:			$(OBJ)

$(OBJDIR) $(CRTDIR) $(CIRCLE_DIR):			
				mkdir -p $@

$(CRTDIR)/startup.o:		circle/lib/startup.o $(HEADERS)
				$(INSTALL) $< $@

$(CRTDIR)/crt0.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crti.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crtn.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crtbegin.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crtbeginT.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(CRTDIR)/crtend.o:		$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $@ -x c -

$(LIBG):			$(CRTDIR)
				printf "\n" | $(COMPILE.c) -o $(OBJDIR)/g.o -x c -
				$(AR) cr $@ $(OBJDIR)/g.o
				$(RANLIB) $@
				rm -f $(OBJDIR)/g.o
				
$(OBJDIR)/clock_getres.o:	clock_getres.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_getres.c

$(OBJDIR)/clock_gettime.o:	clock_gettime.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_gettime.c

$(OBJDIR)/clock_nanosleep.o:	clock_nanosleep.c $(HEADERS)
				$(COMPILE.c) -o $@ clock_nanosleep.c

$(OBJDIR)/_exit.o:		_exit.c $(HEADERS)
				$(COMPILE.c) -o $@ _exit.c

$(OBJDIR)/fcntl.o:		fcntl.c $(HEADERS)
				$(COMPILE.c) -o $@ fcntl.c

$(OBJDIR)/fstat.o:		fstat.c $(HEADERS)
				$(COMPILE.c) -o $@ fstat.c

$(OBJDIR)/fsync.o:		fsync.c $(HEADERS)
				$(COMPILE.c) -o $@ fsync.c

$(OBJDIR)/getpagesize.o:	getpagesize.c $(HEADERS)
				$(COMPILE.c) -o $@ getpagesize.c

$(OBJDIR)/getrandom.o:		getrandom.c $(HEADERS)
				$(COMPILE.c) -o $@ getrandom.c

$(OBJDIR)/kill.o:		kill.c $(HEADERS)
				$(COMPILE.c) -o $@ kill.c

$(OBJDIR)/__libc_start_main.o:	__libc_start_main.c $(HEADERS)
				$(COMPILE.c) -o $@ __libc_start_main.c

$(OBJDIR)/lseek.o:		lseek.c $(HEADERS)
				$(COMPILE.c) -o $@ lseek.c

$(OBJDIR)/mmap.o:		mmap.c $(HEADERS)
				$(COMPILE.c) -o $@ mmap.c

$(OBJDIR)/mprotect.o:		mprotect.c
				$(COMPILE.c) -o $@ mprotect.c

$(OBJDIR)/poll.o:		poll.c $(HEADERS)
				$(COMPILE.c) -o $@ poll.c

$(OBJDIR)/pread.o:		pread.c $(HEADERS)
				$(COMPILE.c) -o $@ pread.c

$(OBJDIR)/preadv.o:		preadv.c $(HEADERS)
				$(COMPILE.c) -o $@ preadv.c

$(OBJDIR)/pwrite.o:		pwrite.c $(HEADERS)
				$(COMPILE.c) -o $@ pwrite.c

$(OBJDIR)/pwritev.o:		pwritev.c $(HEADERS)
				$(COMPILE.c) -o $@ pwritev.c

$(OBJDIR)/read.o:		read.c $(HEADERS)
				$(COMPILE.c) -o $@ read.c

$(OBJDIR)/readv.o:		readv.c $(HEADERS)
				$(COMPILE.c) -o $@ readv.c

$(OBJDIR)/write.o:		write.c $(HEADERS)
				$(COMPILE.c) -o $@ write.c

$(OBJDIR)/writev.o:		writev.c $(HEADERS)
				$(COMPILE.c) -o $@ writev.c

$(CIRCLE_DIR)/libcircle.a: 	circle/lib/libcircle.a $(HEADERS)
				$(INSTALL) $< $@

$(CIRCLE_DIR)/libcircle_net.a:	circle/lib/net/libnet.a $(HEADERS)
				$(INSTALL) $< $@

$(CIRCLE_DIR)/libcircle_usb.a:	circle/lib/usb/libusb.a $(HEADERS)
				$(INSTALL) $< $@

circle/lib/libcircle.a circle/lib/startup.o:
				$(MAKE) -C circle/lib $(CIRCLE_FLAGS)

circle/lib/net/libnet.a:
				$(MAKE) -C circle/lib/net $(CIRCLE_FLAGS)

circle/lib/usb/libusb.a:
				$(MAKE) -C circle/lib/usb $(CIRCLE_FLAGS)

.PHONY:				clean
clean:		
				rm -f $(OBJ)
				$(MAKE) -C circle/lib clean
				$(MAKE) -C circle/lib/net clean
				$(MAKE) -C circle/lib/usb clean
