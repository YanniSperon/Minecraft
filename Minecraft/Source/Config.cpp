#include "Config.h"
#include "Console.h"

#include <string>
#include <iostream>
#include <fstream>

Config::Config()
	: m_StartingWidth(1280), m_StartingHeight(720), m_HasVSync(0)
{
	Load();
}

void Config::Save()
{
	std::ofstream configFile("Resources/Config.cfg");

	if (configFile.is_open()) {
		configFile << "VSync=" << m_HasVSync << "\n";
		configFile << "StartingWidth=" << m_StartingWidth << "\n";
		configFile << "StartingHeight=" << m_StartingHeight << "\n";
	}
	else {
		Console::Error("Failed to save config");
	}

	configFile.close();
}

void Config::Load()
{
	std::ifstream configFile("Resources/Config.cfg");

	if (configFile.is_open()) {
		std::string line;
		while (std::getline(configFile, line))
		{
			if (line.find("VSync=") != std::string::npos) {
				std::string value = line.substr(6);
				Console::Warning("VSync: \"%s\"", value.c_str());
				m_HasVSync = std::stoi(value);
			}
			else if (line.find("StartingWidth=") != std::string::npos) {
				std::string value = line.substr(14);
				Console::Warning("StartingWidth: \"%s\"", value.c_str());
				m_StartingWidth = std::stoi(value);
				Console::Warning("StartingWidth: \"%i\"", m_StartingWidth);
			}
			else if (line.find("StartingHeight=") != std::string::npos) {
				std::string value = line.substr(15);
				Console::Warning("StartingHeight: \"%s\"", value.c_str());
				m_StartingHeight = std::stoi(value);
				Console::Warning("StartingHeight: \"%i\"", m_StartingHeight);
			}
		}
	}
	else {
		Console::Error("Failed to load config");
	}

	configFile.close();
}

bool Config::GetStartingWidth()
{
	return m_StartingWidth;
}

bool Config::GetStartingHeight()
{
	return m_StartingHeight;
}

bool Config::GetHasVSync()
{
	return m_HasVSync;
}

void Config::SetStartingWidth(unsigned int width)
{
	m_StartingWidth = width;
	Save();
}

void Config::SetStartingHeight(unsigned int height)
{
	m_StartingHeight = height;
	Save();
}

void Config::SetHasVSync(bool hasVSync)
{
	m_HasVSync = hasVSync;
	Save();
}