#include "GUI.h"
#include "Global.h"

#include "Vendor/ImGui/imgui_impl_glfw_gl3.h"

#include <cstdio>
#include <cstdarg>

static bool s_InitializedIMGUI = false;

#define GUI_INDENTATION_SIZE 5.0f
#define GUI_FONT_SIZE 20.0f

MC::GUI::GUI(GLFWwindow* window)
    : m_Font(nullptr), m_IO(nullptr), m_Style(nullptr)
{
    if (!s_InitializedIMGUI) {
        //////////////////////////////////////////////////////////////////////////////////////////////
        ImGui::CreateContext();
        m_IO = &ImGui::GetIO();
        m_IO->IniFilename = nullptr;
        //////////////////////////////////////////////////////////////////////////////////////////////
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();
        //////////////////////////////////////////////////////////////////////////////////////////////
        m_Style = &ImGui::GetStyle();
        m_Style->WindowBorderSize = 0.0f;
        m_Style->ChildBorderSize = 0.0f;
        m_Style->PopupBorderSize = 0.0f;
        m_Style->FrameBorderSize = 0.0f;
        m_Style->IndentSpacing = 0.0f;
        m_Style->FramePadding = ImVec2(0.0f, 0.0f);
        m_Style->WindowPadding = ImVec2(GUI_INDENTATION_SIZE, GUI_INDENTATION_SIZE);
        //style.ItemSpacing = ImVec2(8.0f, 4.0f); default
        m_Style->ItemSpacing = ImVec2(0.0f, 4.0f);
        //////////////////////////////////////////////////////////////////////////////////////////////
        m_Font = m_IO->Fonts->AddFontFromFileTTF("E:\\Programming\\Visual Studio Programs\\Minecraft\\Minecraft\\Resources\\Minecraft.ttf", GUI_FONT_SIZE);
        //////////////////////////////////////////////////////////////////////////////////////////////
        s_InitializedIMGUI = true;
        //////////////////////////////////////////////////////////////////////////////////////////////
    }
}

MC::GUI::~GUI()
{
    if (s_InitializedIMGUI) {
        ImGui_ImplGlfwGL3_Shutdown();
        ImGui::DestroyContext();
        s_InitializedIMGUI = false;
    }
}

void MC::GUI::PlaceTextLeft(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char* txt = new char[1024];
    vsnprintf(txt, 1024, fmt, args);
    std::string returnValue = std::string(txt);
    LeftHorizontalAlignText(GUI_INDENTATION_SIZE);
    ImGui::Text("%s", returnValue.c_str());
    va_end(args);
    delete[] txt;
}

void MC::GUI::PlaceTextCenter(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char* txt = new char[1024];
    vsnprintf(txt, 1024, fmt, args);
    std::string returnValue = std::string(txt);
    GUI::CenterHorizontalAlignText(returnValue);
    ImGui::Text("%s", returnValue.c_str());
    va_end(args);
    delete[] txt;
}

void MC::GUI::PlaceTextRight(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char* txt = new char[1024];
    vsnprintf(txt, 1024, fmt, args);
    std::string returnValue = std::string(txt);
    GUI::RightHorizontalAlignText(returnValue, GUI_INDENTATION_SIZE);
    ImGui::Text("%s", returnValue.c_str());
    va_end(args);
    delete[] txt;
}

void MC::GUI::SameLine()
{
    ImGui::SameLine();
}

void MC::GUI::LeftHorizontalAlignText(float indent)
{
    ImGui::SetCursorPosX(indent);
}

void MC::GUI::CenterHorizontalAlignText(const std::string& text)
{
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - GetTextSizeX(text)) * 0.5f);
}

void MC::GUI::RightHorizontalAlignText(const std::string& text, float indent)
{
	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - GetTextSizeX(text) - indent);
}

float MC::GUI::GetTextSizeX(const std::string& text)
{
	return ImGui::CalcTextSize(text.c_str()).x;
}

float MC::GUI::GetTextSizeY(const std::string& text)
{
	return ImGui::CalcTextSize(text.c_str()).y;
}