#include "Input.h"
#include "Console.h"
#include "Devices.h"
#include "GUI.h"
#include "Global.h"

#include <glew.h>
#include <glfw3.h>
#include <chrono>

#include "Vendor/ImGui/imgui.h"
#include "Vendor/ImGui/imgui_impl_glfw_gl3.h"

using namespace MC;

int main() {
    //////////////////////////////////////////////////////////////////////////////////////////////

    Global::Initialize();

    //////////////////////////////////////////////////////////////////////////////////////////////

    double timeConstant = 1.0;
    auto lastTime = std::chrono::high_resolution_clock::now();
    auto currentTime = lastTime;

    //////////////////////////////////////////////////////////////////////////////////////////////

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    bool shouldDisplayDebugInfo = true;

    //////////////////////////////////////////////////////////////////////////////////////////////

    while (!glfwWindowShouldClose(Global::GetWindow().GetGLFWwindow()))
    {
        //////////////////////////////////////////////////////////////////////////////////////////////

        currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTimeNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime);
        lastTime = currentTime;
        double deltaTime = deltaTimeNanoseconds.count() / 1000000000.0 * timeConstant;

        //////////////////////////////////////////////////////////////////////////////////////////////

        Global::GetWindow().PollEvents();
        Input::ProcessEvents(Global::GetKeyboardInput(), Global::GetMouseInput());
        
        //////////////////////////////////////////////////////////////////////////////////////////////

        if (Global::GetKeyboardInput().m_KeysPressed[MC_KEY_F3]) {
            shouldDisplayDebugInfo = !shouldDisplayDebugInfo;
        }

        //////////////////////////////////////////////////////////////////////////////////////////////

        Global::GetWindow().ClearBuffer();

        //////////////////////////////////////////////////////////////////////////////////////////////

        ImGui_ImplGlfwGL3_NewFrame();
        //ImGui::PushFont(customFont);
        if (shouldDisplayDebugInfo) {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
            ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
            ImGui::SetNextWindowSize(ImVec2(Global::GetWindow().GetWidth(), Global::GetWindow().GetHeight()));
            ImGui::Begin("Debug##F3Menu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs);
            //ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("%s", Devices::GetClientVersion().c_str());
            ImGui::SameLine(ImGui::GetWindowSize().x / 2.0f);
            ImGui::Text("%s", Devices::GetCPPVersion().c_str());
            ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
            ImGui::Text("%s", Devices::GetServerVersion().c_str());
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::Text("XYZ: 0.0 / 0.0 / 0.0");
            ImGui::End();
            ImGui::SetNextWindowPos(ImVec2(1000.0f, 0.0f));
            ImGui::SetNextWindowSize(ImVec2(519.0f, 144.0f));
            ImGui::Begin("Debug##F3MenuRight", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs);
            //ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            GUI::RightHorizontalAlignText(Devices::GetCPPVersion());
            ImGui::Text("%s", Devices::GetCPPVersion().c_str());
            GUI::RightHorizontalAlignText("Total Memory: " + Devices::GetInstalledMemory());
            ImGui::Text("Total Memory: %s", Devices::GetInstalledMemory().c_str());
            GUI::RightHorizontalAlignText("Used Memory: " + Devices::GetUsedMemory());
            ImGui::Text("Used Memory: %s", Devices::GetUsedMemory().c_str());
            GUI::RightHorizontalAlignText("CPU: " + Devices::GetCPUVersion());
            ImGui::Text("CPU: %s", Devices::GetCPUVersion().c_str());
            //Console::Info("Current Window Size: {%f, %f}", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);
            ImGui::Spacing();
            ImGui::Spacing();
            GUI::RightHorizontalAlignText("Display: 1920x1080");
            ImGui::Text("Display: 1920x1080");
            GUI::RightHorizontalAlignText(Devices::GetGPUVersion());
            ImGui::Text("%s", Devices::GetGPUVersion().c_str());
            GUI::RightHorizontalAlignText(Devices::GetGLVersion());
            ImGui::Text("%s", Devices::GetGLVersion().c_str());
            ImGui::End();
            ImGui::PopStyleColor();
        }
        //ImGui::PopFont();
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        //////////////////////////////////////////////////////////////////////////////////////////////

        Global::GetWindow().SwapBuffers();

        //////////////////////////////////////////////////////////////////////////////////////////////

        Input::Flush(Global::GetKeyboardInput(), Global::GetMouseInput());

        //////////////////////////////////////////////////////////////////////////////////////////////
    }

    glfwTerminate();
    return 0;

    //////////////////////////////////////////////////////////////////////////////////////////////
}