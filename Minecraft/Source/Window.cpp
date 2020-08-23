#include "Window.h"
#include "Global.h"
#include "Console.h"
#include "Input.h"
#include "GUI/GUI.h"

#include <glew.h>

static bool s_InitializedGL = false;

MC::Window::Window()
    : m_Window(nullptr), m_Width(Global::GetConfig().GetStartingWidth()), m_Height(Global::GetConfig().GetStartingHeight()), m_GUI(nullptr), m_CurrentScene(std::make_unique<Scene>()), m_CurrentShaderID(0)
{
    if (!s_InitializedGL) {
        //////////////////////////////////////////////////////////////////////////////////////////////
        Console::Assert(glfwInit(), "Failed GLFW Initialization!");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        //////////////////////////////////////////////////////////////////////////////////////////////
        m_Window = glfwCreateWindow(m_Width, m_Height, "Minecraft", NULL, NULL);
        Console::Assert(m_Window, "Failed Window Creation!");
        glfwMakeContextCurrent(m_Window);
        //////////////////////////////////////////////////////////////////////////////////////////////
        GLenum err = glewInit();
        Console::Assert(err == GLEW_OK, "Failed GLEW Initialization - %s", reinterpret_cast<char const*>(glewGetErrorString(err)));
        //////////////////////////////////////////////////////////////////////////////////////////////
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_CCW);
        //////////////////////////////////////////////////////////////////////////////////////////////
        glDebugMessageCallback(Window::GLDebugMessageCallback, 0);
        //////////////////////////////////////////////////////////////////////////////////////////////
        glfwSwapInterval(Global::GetConfig().GetHasVSync());
        //////////////////////////////////////////////////////////////////////////////////////////////
        if (glfwRawMouseMotionSupported()) {
            glfwSetInputMode(m_Window, GLFW_RAW_MOUSE_MOTION, Global::GetConfig().GetHasRawMouseInput());
        }
        else {
            Global::GetConfig().SetHasRawMouseInput(false);
        }
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
        glfwDestroyWindow(m_Window);
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

MC::Scene& MC::Window::GetCurrentScene()
{
    return *m_CurrentScene;
}

GLuint MC::Window::GetCurrentShaderID()
{
    return m_CurrentShaderID;
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

void MC::Window::SetCurrentScene(std::unique_ptr<Scene> scene)
{
    m_CurrentScene = std::move(scene);
}

void MC::Window::SetCurrentShaderID(GLuint shaderID)
{
    m_CurrentShaderID = shaderID;
}

void MC::Window::ReplaceGUI(GUI* gui)
{
    delete m_GUI;
    m_GUI = gui;
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

void MC::Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
    Global::GetWindow().SetWidth(width);
    Global::GetWindow().SetHeight(height);
}

void GLAPIENTRY MC::Window::GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        Console::FatalError("GL CALLBACK:%s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? " ** GL ERROR **" : ""), type, severity, message);
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        Console::Error("GL CALLBACK:%s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? " ** GL ERROR **" : ""), type, severity, message);
        break;
    case GL_DEBUG_SEVERITY_LOW:
        Console::Warning("GL CALLBACK:%s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? " ** GL ERROR **" : ""), type, severity, message);
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        Console::Info("GL NOTIFICATION:%s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? " ** GL ERROR **" : ""), type, severity, message);
        break;
    }
}