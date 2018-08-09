#include <circle/startup.h>
#include <unistd.h>

static inline void qemu_halt(int status)
{
	switch (status) {
	case 0:
		__asm__ __volatile__("mov r0, #0x18;\n"
				     "ldr r1, =0x20026\n"
				     "svc 0x00123456;\n" ::
					     : "r0", "r1");
		break;
	default:
		__asm__ __volatile__("mov r0, #0x18;\n"
				     "mov r1, %0\n"
				     "svc 0x00123456;\n" ::"r"(status)
				     : "r0", "r1");
		break;
	}
}

static inline void raspi_halt(int status)
{
	switch (status) {
	case EXIT_REBOOT:
		reboot();
		break;
	default:
		halt();
		break;
	}
}

void _exit(int status)
{
#ifdef CIRCLE_USE_QEMU
	qemu_halt();
#else
	raspi_halt();
#endif
}
