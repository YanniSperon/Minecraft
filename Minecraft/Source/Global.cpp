#include "Global.h"
#include "Console.h"

#include <memory>

static std::vector<std::string> g_ConsoleLog;
static std::chrono::steady_clock::time_point g_SystemStartTime;
static std::string g_MCVersion;
static std::unique_ptr<Config> g_Config;
static std::unique_ptr<MC::Window> g_Window;
static std::unique_ptr<MC::KeyboardInput> g_KeyboardInput;
static std::unique_ptr<MC::MouseInput> g_MouseInput;
static std::unique_ptr<MC::Mesh3DManager> g_Mesh3DManager;
static std::unique_ptr<MC::ShaderManager> g_ShaderManager;
static std::unique_ptr<MC::TextureManager> g_TextureManager;

void Global::Initialize()
{
	g_ConsoleLog = std::vector<std::string>();
	g_SystemStartTime = std::chrono::high_resolution_clock::now();
	g_MCVersion = "1.0.0";

	g_Config = std::make_unique<Config>();
	g_Window = std::make_unique<MC::Window>();
	g_KeyboardInput = std::make_unique<MC::KeyboardInput>();
	g_MouseInput = std::make_unique<MC::MouseInput>();
	g_Mesh3DManager = std::make_unique<MC::Mesh3DManager>();
	g_ShaderManager = std::make_unique<MC::ShaderManager>();
	g_TextureManager = std::make_unique<MC::TextureManager>();
}

std::chrono::steady_clock::time_point& Global::GetStartTime()
{
	return g_SystemStartTime;
}

std::vector<std::string>& Global::GetConsoleLog()
{
	return g_ConsoleLog;
}

std::string& Global::GetMCVersion()
{
	return g_MCVersion;
}

Config& Global::GetConfig()
{
	return *g_Config;
}

MC::Window& Global::GetWindow()
{
	return *g_Window;
}

MC::KeyboardInput& Global::GetKeyboardInput()
{
	return *g_KeyboardInput;
}

MC::MouseInput& Global::GetMouseInput()
{
	return *g_MouseInput;
}

MC::Mesh3DManager& Global::GetMesh3DManager()
{
	return *g_Mesh3DManager;
}

MC::ShaderManager& Global::GetShaderManager()
{
	return *g_ShaderManager;
}

MC::TextureManager& Global::GetTextureManager()
{
	return *g_TextureManager;
}
