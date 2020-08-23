#include "GUI.h"
#include "Global.h"
#include "Devices.h"

#include "Vendor/ImGui/imgui_impl_glfw_gl3.h"

#include <cstdio>
#include <cstdarg>

static bool s_InitializedIMGUI = false;

#define GUI_INDENTATION_SIZE 5.0f
#define GUI_FONT_SIZE 20.0f

MC::GUI::GUI(GLFWwindow* window)
    : m_Font(nullptr), m_IO(nullptr), m_Style(nullptr), m_ShouldDisplayDebugInfo(false), m_ShouldDisplayInventory(false), m_ShouldDisplayMenu(false)
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

void MC::GUI::Begin()
{
    ImGui_ImplGlfwGL3_NewFrame();
}

void MC::GUI::DisplayDebugInfo()
{
    if (m_ShouldDisplayDebugInfo) {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        ImGui::SetNextWindowSize(ImVec2(Global::GetWindow().GetWidth(), Global::GetWindow().GetHeight()));
        ImGui::Begin("Debug##F3Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs);

        GUI::PlaceTextLeft("%s", Devices::GetClientVersion().c_str());
        GUI::SameLine();
        GUI::PlaceTextRight("%s", Devices::GetCPPVersion().c_str());

        GUI::PlaceTextLeft("%.1f FPS", ImGui::GetIO().Framerate);
        GUI::SameLine();
        GUI::PlaceTextRight("Total Memory: %s", Devices::GetInstalledMemory().c_str());

        GUI::PlaceTextLeft("%s", Devices::GetServerVersion().c_str());
        GUI::SameLine();
        GUI::PlaceTextRight("Used Memory: %s", Devices::GetUsedMemory().c_str());

        GUI::PlaceTextRight("CPU: %s", Devices::GetCPUVersion().c_str());

        glm::vec3 cameraTranslation = Global::GetWindow().GetCurrentScene().GetCurrentCamera().GetTranslation();
        GUI::PlaceTextLeft("XYZ: %.3f / %.3f / %.3f", cameraTranslation.x, cameraTranslation.y, cameraTranslation.z);

        GUI::PlaceTextRight("Display: %ix%i", Global::GetWindow().GetWidth(), Global::GetWindow().GetHeight());

        GUI::PlaceTextRight("%s", Devices::GetGPUVersion().c_str());

        GUI::PlaceTextRight("%s", Devices::GetGLVersion().c_str());

        ImGui::End();

        ImGui::PopStyleColor();
    }
}

void MC::GUI::DisplayInventory()
{
    if (m_ShouldDisplayInventory) {

    }
}

void MC::GUI::DisplayMenu()
{
    if (m_ShouldDisplayMenu) {

    }
}

void MC::GUI::End()
{
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

bool MC::GUI::GetShouldDisplayDebugInfo()
{
    return m_ShouldDisplayDebugInfo;
}

bool MC::GUI::GetShouldDisplayInventory()
{
    return m_ShouldDisplayInventory;
}

bool MC::GUI::GetShouldDisplayMenu()
{
    return m_ShouldDisplayMenu;
}

void MC::GUI::SetShouldDisplayDebugInfo(bool shouldDisplayDebugInfo)
{
    m_ShouldDisplayDebugInfo = shouldDisplayDebugInfo;
}

void MC::GUI::SetShouldDisplayInventory(bool shouldDisplayInventory)
{
    m_ShouldDisplayInventory = shouldDisplayInventory;
}

void MC::GUI::SetShouldDisplayMenu(bool shouldDisplayMenu)
{
    m_ShouldDisplayMenu = shouldDisplayMenu;
}

void MC::GUI::ToggleShouldDisplayDebugInfo()
{
    m_ShouldDisplayDebugInfo = !m_ShouldDisplayDebugInfo;
}

void MC::GUI::ToggleShouldDisplayInventory()
{
    m_ShouldDisplayInventory = !m_ShouldDisplayInventory;
}

void MC::GUI::ToggleShouldDisplayMenu()
{
    m_ShouldDisplayMenu = !m_ShouldDisplayMenu;
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