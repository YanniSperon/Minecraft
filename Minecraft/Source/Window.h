#pragma once

#include "GUI/GUI.h"
#include "3D/Scene/Scene.h"

#include <glew.h>
#include <glfw3.h>
#include <memory>

namespace MC {
	class Window {
	private:
		GLFWwindow* m_Window;
		int m_Width, m_Height;
		GUI* m_GUI;
		std::unique_ptr<Scene> m_CurrentScene;
	public:
		Window();
		~Window();

		int GetWidth();
		int GetHeight();
		GLFWwindow* GetGLFWwindow();
		GUI& GetGUI();
		Scene& GetCurrentScene();

		void SetWidth(int width);
		void SetHeight(int height);
		void SetGLFWwindow(GLFWwindow* window);
		void SetGUI(GUI* gui);
		void SetCurrentScene(std::unique_ptr<Scene> scene);

		void ReplaceGUI(GUI* gui);


		void PollEvents();
		void ClearBuffer();
		void SwapBuffers();

		bool ShouldCloseWindow();

		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		static void GLAPIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
	};
}