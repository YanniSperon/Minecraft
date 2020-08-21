#pragma once

#include "GUI/GUI.h"

#include <glew.h>
#include <glfw3.h>
#include <memory>

namespace MC {
	class Window {
	private:
		GLFWwindow* m_Window;
		int m_Width, m_Height;
		GUI* m_GUI;
	public:
		Window();
		~Window();

		int GetWidth();
		int GetHeight();
		GLFWwindow* GetGLFWwindow();
		GUI& GetGUI();

		void SetWidth(int width);
		void SetHeight(int height);
		void SetGLFWwindow(GLFWwindow* window);
		void SetGUI(GUI* gui);

		void ReplaceGUI(GUI* gui);

		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		static void GLAPIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

		void PollEvents();
		void ClearBuffer();
		void SwapBuffers();

		bool ShouldCloseWindow();
	};
}