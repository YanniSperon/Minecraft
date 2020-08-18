#pragma once

#include "GUI.h"

#include <glfw3.h>
#include <memory>

namespace MC {
	class Window {
	private:
		GLFWwindow* m_Window;
		unsigned int m_Width, m_Height;
		GUI* m_GUI;
	public:
		Window();
		~Window();

		unsigned int GetWidth();
		unsigned int GetHeight();
		GLFWwindow* GetGLFWwindow();
		GUI& GetGUI();

		void SetWidth(unsigned int width);
		void SetHeight(unsigned int height);
		void SetGLFWwindow(GLFWwindow* window);
		void SetGUI(GUI* gui);

		void ReplaceGUI(GUI* gui);

		static void WindowSizeCallback(GLFWwindow* window, int width, int height);

		void PollEvents();
		void ClearBuffer();
		void SwapBuffers();
	};
}