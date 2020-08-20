#include "Window.h"
#include "Global.h"
#include "Console.h"
#include "Input.h"
#include "GUI/GUI.h"

#include <glew.h>

static bool s_InitializedGL = false;

MC::Window::Window()
    : m_Window(nullptr), m_Width(Global::GetConfig().GetStartingWidth()), m_Height(Global::GetConfig().GetStartingHeight()), m_GUI(nullptr)
{
    if (!s_InitializedGL) {
        //////////////////////////////////////////////////////////////////////////////////////////////
        Console::Assert(glfwInit(), "Failed GLFW Initialization!");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //////////////////////////////////////////////////////////////////////////////////////////////
        m_Window = glfwCreateWindow(m_Width, m_Height, "Minecraft", NULL, NULL);
        if (m_Window) {
            Console::Info("Succeeded creation");
        }
        else {
            Console::Info("Failed creation");
        }
        //Console::Assert(!m_Window, "Failed Window Creation!");
        glfwMakeContextCurrent(m_Window);
        //////////////////////////////////////////////////////////////////////////////////////////////
        GLenum err = glewInit();
        Console::Assert(err == GLEW_OK, "Failed GLEW Initialization - %s", reinterpret_cast<char const*>(glewGetErrorString(err)));
        //////////////////////////////////////////////////////////////////////////////////////////////
        glfwSetCursorPosCallback(m_Window, Input::MousePositionCallback);
        glfwSetKeyCallback(m_Window, Input::KeyCallback);
        glfwSetWindowSizeCallback(m_Window, Window::WindowSizeCallback);
        //////////////////////////////////////////////////////////////////////////////////////////////
    }
    m_GUI = new GUI(m_Window);
    //////////////////////////////////////////////////////////////////////////////////////////////
}

MC::Window::~Window()
{
    if (s_InitializedGL) {
        glfwTerminate();
        s_InitializedGL = false;
    }
    delete m_GUI;
}

int MC::Window::GetWidth()
{
    return m_Width;
}

int MC::Window::GetHeight()
{
    return m_Height;
}

GLFWwindow* MC::Window::GetGLFWwindow()
{
    return m_Window;
}

MC::GUI& MC::Window::GetGUI()
{
    return *m_GUI;
}

void MC::Window::SetWidth(int width)
{
    m_Width = width;
}

void MC::Window::SetHeight(int height)
{
    m_Height = height;
}

void MC::Window::SetGLFWwindow(GLFWwindow* window)
{
    m_Window = window;
}

void MC::Window::SetGUI(GUI* gui)
{
    m_GUI = gui;
}

void MC::Window::ReplaceGUI(GUI* gui)
{
    delete m_GUI;
    m_GUI = gui;
}

void MC::Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    Global::GetWindow().SetWidth(width);
    Global::GetWindow().SetHeight(height);
}

void MC::Window::PollEvents()
{
    glfwPollEvents();
}

void MC::Window::ClearBuffer()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MC::Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

bool MC::Window::ShouldCloseWindow()
{
    return glfwWindowShouldClose(m_Window);
}
