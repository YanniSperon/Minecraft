#include "GUI.h"
#include "Global.h"

#include "Vendor/ImGui/imgui_impl_glfw_gl3.h"

static bool s_InitializedIMGUI = false;

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
        m_Style->WindowPadding = ImVec2(0.0f, 0.0f);
        //style.ItemSpacing = ImVec2(8.0f, 4.0f); default
        m_Style->ItemSpacing = ImVec2(0.0f, 4.0f);
        //////////////////////////////////////////////////////////////////////////////////////////////
        m_Font = m_IO->Fonts->AddFontFromFileTTF("E:\\Programming\\Visual Studio Programs\\Minecraft\\Minecraft\\Resources\\Minecraft.ttf", 16.0f);
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

void MC::GUI::CenterHorizontalAlign(float itemWidth)
{
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - itemWidth) * 0.5f);
}

void MC::GUI::RightHorizontalAlign(float itemWidth, float indent)
{
	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - itemWidth - indent);
}

void MC::GUI::CenterHorizontalAlignText(std::string text)
{
	ImGui::SetCursorPosX((ImGui::GetWindowSize().x - GetTextSizeX(text)) * 0.5f);
}

void MC::GUI::RightHorizontalAlignText(std::string text, float indent)
{
	ImGui::SetCursorPosX(ImGui::GetWindowSize().x - GetTextSizeX(text) - indent);
}

float MC::GUI::GetTextSizeX(std::string text)
{
	return ImGui::CalcTextSize(text.c_str()).x;
}

float MC::GUI::GetTextSizeY(std::string text)
{
	return ImGui::CalcTextSize(text.c_str()).y;
}