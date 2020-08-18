#include "Console.h"
#include "Global.h"

#include <cstdio>
#include <cstdarg>
#include <chrono>
#include <mutex>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#endif

static std::mutex printMutex;

void Console::Success(const char* fmt, ...)
{
	printMutex.lock();
	va_list args;
	va_start(args, fmt);
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::GetStartTime());
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
#endif
	std::string timestampString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- SUCCESS:      ";
	char* message = new char[1024];
	vsprintf(message, fmt, args);
	std::string returnValue = timestampString + std::string(message);
	printf("%s\n", returnValue.c_str());
	Global::GetConsoleLog().push_back(returnValue);
	if (Global::GetConsoleLog().size() > 50) {
		Global::GetConsoleLog().erase(Global::GetConsoleLog().begin());
	}
	va_end(args);
	delete[] message;
	printMutex.unlock();
}

void Console::Info(const char* fmt, ...)
{
	printMutex.lock();
	va_list args;
	va_start(args, fmt);
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::GetStartTime());
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
#endif
	std::string timestampString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- INFO:         ";
	char* message = new char[1024];
	vsprintf(message, fmt, args);
	std::string returnValue = timestampString + std::string(message);
	printf("%s\n", returnValue.c_str());
	Global::GetConsoleLog().push_back(returnValue);
	if (Global::GetConsoleLog().size() > 50) {
		Global::GetConsoleLog().erase(Global::GetConsoleLog().begin());
	}
	va_end(args);
	delete[] message;
	printMutex.unlock();
}

void Console::Warning(const char* fmt, ...)
{
	printMutex.lock();
	va_list args;
	va_start(args, fmt);
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::GetStartTime());
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
#endif
	std::string timestampString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- WARNING:      ";
	char* message = new char[1024];
	vsprintf(message, fmt, args);
	std::string returnValue = timestampString + std::string(message);
	printf("%s\n", returnValue.c_str());
	Global::GetConsoleLog().push_back(returnValue);
	if (Global::GetConsoleLog().size() > 50) {
		Global::GetConsoleLog().erase(Global::GetConsoleLog().begin());
	}
	va_end(args);
	delete[] message;
	printMutex.unlock();
}

void Console::Error(const char* fmt, ...)
{
	printMutex.lock();
	va_list args;
	va_start(args, fmt);
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::GetStartTime());
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
#endif
	std::string timestampString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- ERROR:        ";
	char* message = new char[1024];
	vsprintf(message, fmt, args);
	std::string returnValue = timestampString + std::string(message);
	printf("%s\n", returnValue.c_str());
	Global::GetConsoleLog().push_back(returnValue);
	if (Global::GetConsoleLog().size() > 50) {
		Global::GetConsoleLog().erase(Global::GetConsoleLog().begin());
	}
	va_end(args);
	delete[] message;
	printMutex.unlock();
}

void Console::FatalError(const char* fmt, ...)
{
	printMutex.lock();
	va_list args;
	va_start(args, fmt);
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - Global::GetStartTime());
	auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
	auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration - hours);
	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration - hours - minutes);
	auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - hours - minutes - seconds);
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - hours - minutes - seconds - milliseconds);
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 79);
#endif
	std::string timestampString = std::to_string(hours.count()) + ":" + std::to_string(minutes.count()) + ":" + std::to_string(seconds.count()) + "." + std::to_string(milliseconds.count()) + std::to_string(microseconds.count()) + " -- FATAL ERROR:  ";
	char* message = new char[1024];
	vsprintf(message, fmt, args);
	std::string returnValue = timestampString + std::string(message);
	printf("%s\n", returnValue.c_str());
	Global::GetConsoleLog().push_back(returnValue);
	if (Global::GetConsoleLog().size() > 50) {
		Global::GetConsoleLog().erase(Global::GetConsoleLog().begin());
	}
	va_end(args);
	delete[] message;
	printMutex.unlock();
}

void Console::Assert(bool value, const char* fmt, ...)
{
#ifdef MC_DEBUG
	if (!value) {
		va_list args;
		va_start(args, fmt);
		FatalError(fmt, args);
		va_end(args);
	}
#endif
}