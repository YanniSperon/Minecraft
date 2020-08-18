#pragma once

#include <string>

class Devices {
public:
	static std::string GetClientVersion();
	static std::string GetServerVersion();
	static std::string GetGLVersion();
	static std::string GetCPUVersion();
	static std::string GetGPUVersion();
	static std::string GetInstalledMemory();
	static std::string GetUsedMemory();
	static std::string GetCPPVersion();
};