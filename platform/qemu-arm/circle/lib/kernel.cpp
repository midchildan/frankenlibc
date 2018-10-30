#include <circle/kernel.h>
#include <circle/startup.h>
#include "../../include/raspi.h"

#define CKERNEL_INIT(dev, ...)                                                 \
	if (!(dev).Initialize(__VA_ARGS__)) {                                  \
		return FALSE;                                                  \
	}

static CKernel *s_kernel = nullptr;

CKernel::CKernel(void)
	: m_Screen(m_Options.GetWidth(), m_Options.GetHeight()),
	  m_Timer(&m_Interrupt), m_Logger(m_Options.GetLogLevel(), &m_Timer),
	  m_DWHCI(&m_Interrupt, &m_Timer)
{
	m_ActLED.Blink(5); // show we are alive
}

boolean CKernel::Initialize(void)
{
	CKERNEL_INIT(m_Screen);
	CKERNEL_INIT(m_Serial, 115200);

	const char* logdevice = m_Options.GetLogDevice();
	m_logDst = m_DeviceNameService.GetDevice(logdevice, FALSE);
	if (m_logDst == nullptr) {
		m_logDst = &m_Screen;
	}

	CKERNEL_INIT(m_Logger, m_logDst);
	CKERNEL_INIT(m_Interrupt);
	CKERNEL_INIT(m_Timer);
	CKERNEL_INIT(m_DWHCI);

	m_Eth0 = (CNetDevice *)m_DeviceNameService.GetDevice("eth0", FALSE);
	if (m_Eth0 == nullptr) {
		m_Logger.Write("CKernel", LogError, "Net device not found");
		return FALSE;
	}

	return TRUE;
}

size_t __hwcap = 407;
int argc = 1;
const char *argv[2] = { "qemu-arm", "\0" };
const char *envp[2] = { "RUMP_VERBOSE=1", "\0" };

extern "C" int cr_read(void *pBuffer, unsigned nLength)
{
	return s_kernel ? s_kernel->Read(pBuffer, nLength) : 0;
}

extern "C" int cr_write(const void *pBuffer, unsigned nLength)
{
	return s_kernel ? s_kernel->Write(pBuffer, nLength) : 0;
}

extern "C" int cr_sendframe(const void *pBuffer, unsigned nLength)
{
	return s_kernel ? s_kernel->SendFrame(pBuffer, nLength) : 0;
}

// pBuffer must have size FRAME_BUFFER_SIZE
extern "C" int cr_recvframe(void *pBuffer, unsigned *pResultLength)
{
	return s_kernel ? s_kernel->ReceiveFrame(pBuffer, pResultLength) : 0;
}

int cr_main(void)
{
	CKernel kernel;
	s_kernel = &kernel;
	if (!kernel.Initialize()) {
		goto exit;
	}

	__franken_start_main(main, argc, argv, envp);

exit:
	s_kernel = nullptr;
	return EXIT_HALT;
}
