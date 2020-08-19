#pragma once

#include "Window.h"
#include "Input.h"
#include "Config.h"

#include <vector>
#include <string>
#include <chrono>

#include <glfw3.h>

class Global {
public:
	static void Initialize();
	static std::chrono::steady_clock::time_point& GetStartTime();
	static std::vector<std::string>& GetConsoleLog();
	static std::string& GetMCVersion();
	static Config& GetConfig();
	static MC::Window& GetWindow();
	static MC::KeyboardInput& GetKeyboardInput();
	static MC::MouseInput& GetMouseInput();
};