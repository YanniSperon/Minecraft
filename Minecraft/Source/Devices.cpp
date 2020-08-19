#include "Devices.h"
#include "Global.h"

#include <glew.h>
#include <intrin.h>

#ifdef _WIN32
#include <Windows.h>
#endif

std::string Devices::GetClientVersion()
{
	return std::string("Minecraft ") + Global::GetMCVersion();
}

std::string Devices::GetServerVersion()
{
	return std::string("Minecraft Server ") + Global::GetMCVersion();
}

std::string Devices::GetGLVersion()
{
	return std::string((reinterpret_cast<char const*>(glGetString(GL_VERSION))));
}

std::string Devices::GetCPUVersion()
{
#ifdef _WIN32
	int CPUInfo[4] = { -1 };
	__cpuid(CPUInfo, 0x80000000);
	unsigned int nExIds = CPUInfo[0];

	// Get the information associated with each extended ID.
	char CPUBrandString[0x40] = { 0 };
	for (unsigned int i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);

		// Interpret CPU brand string and cache information.
		if (i == 0x80000002)
		{
			memcpy(CPUBrandString,
				CPUInfo,
				sizeof(CPUInfo));
		}
		else if (i == 0x80000003)
		{
			memcpy(CPUBrandString + 16,
				CPUInfo,
				sizeof(CPUInfo));
		}
		else if (i == 0x80000004)
		{
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		}
	}

	return std::string(CPUBrandString);
#else
	return std::string("Unknown");
#endif
}

std::string Devices::GetGPUVersion()
{
	return std::string(reinterpret_cast<char const*>(glGetString(GL_RENDERER)));
}

std::string Devices::GetInstalledMemory()
{
#ifdef _WIN32
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	auto totalPhysicalMemory = memInfo.ullTotalPhys;
	return std::to_string(totalPhysicalMemory / 1024 / 1024) + std::string(" MB");
#else
	return std::string("Unknown");
#endif
}

std::string Devices::GetUsedMemory()
{
#ifdef _WIN32
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	auto usedRam = memInfo.dwMemoryLoad;
	return std::to_string(usedRam) + std::string(" MB");
#else
	return std::string("Unknown");
#endif
}

std::string Devices::GetCPPVersion()
{
	return std::string("CPP Version: ") + std::to_string(__cplusplus) + std::string(" 64 bit");
}
