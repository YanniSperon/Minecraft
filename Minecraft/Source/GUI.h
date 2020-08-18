#pragma once

#include "Vendor/ImGui/imgui.h"
#include <glfw3.h>

#include <string>

namespace MC {
	class GUI {
	private:
		ImGuiStyle* m_Style;
		ImGuiIO* m_IO;
		ImFont* m_Font;
	public:
		GUI(GLFWwindow* window);
		~GUI();

		static void CenterHorizontalAlign(float itemWidth);
		static void RightHorizontalAlign(float itemWidth, float indent = 0.0f);
		//static void SameLineCenter
		static void CenterHorizontalAlignText(std::string text);
		static void RightHorizontalAlignText(std::string text, float indent = 0.0f);
		static float GetTextSizeX(std::string text);
		static float GetTextSizeY(std::string text);
	};
}