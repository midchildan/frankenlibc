#include <string.h>
#include <stdint.h>

#include <uspienv.h>
#include <uspi.h>
#include <uspios.h>

extern int main(int, char **, char **);
//int argc = 1;
//char *argv[2] = {"qemu-arm", "\0"};
int argc = 4;
char *argv[5] = {"ping", "-c", "3", "127.0.0.1", "\0"};
char *envp[2] = {"RUMP_VERBOSE=1", "\0"};

size_t __hwcap = 407;

int
__libc_start_main()
{
	if (!USPiEnvInitialize())
	{
		return EXIT_HALT;
	}

	if (!USPiInitialize())
	{
		LogWrite("uspi", LOG_ERROR, "Cannot initialize USPi");
		USPiEnvClose ();
		return EXIT_HALT;
	}

	return __franken_start_main(main, argc, argv, envp);
}
