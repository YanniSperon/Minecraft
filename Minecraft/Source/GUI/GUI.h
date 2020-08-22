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

		bool m_ShouldDisplayDebugInfo;
		bool m_ShouldDisplayInventory;
		bool m_ShouldDisplayMenu;
	public:
		GUI(GLFWwindow* window);
		~GUI();

		void Begin();
		void DisplayDebugInfo();
		void DisplayInventory();
		void DisplayMenu();
		void End();

		bool GetShouldDisplayDebugInfo();
		bool GetShouldDisplayInventory();
		bool GetShouldDisplayMenu();

		void SetShouldDisplayDebugInfo(bool shouldDisplayDebugInfo);
		void SetShouldDisplayInventory(bool shouldDisplayInventory);
		void SetShouldDisplayMenu(bool shouldDisplayMenu);

		static void PlaceTextLeft(const char* fmt, ...);
		static void PlaceTextCenter(const char* fmt, ...);
		static void PlaceTextRight(const char* fmt, ...);
		static void SameLine();

		static void LeftHorizontalAlignText(float indent = 0.0f);
		static void CenterHorizontalAlignText(const std::string& text);
		static void RightHorizontalAlignText(const std::string& text, float indent = 0.0f);
		static float GetTextSizeX(const std::string& text);
		static float GetTextSizeY(const std::string& text);
	};
}