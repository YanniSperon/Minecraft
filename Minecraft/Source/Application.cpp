#include "Input.h"
#include "Console.h"
#include "Devices.h"
#include "GUI/GUI.h"
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

    while (!Global::GetWindow().ShouldCloseWindow())
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
        if (shouldDisplayDebugInfo) {
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

            GUI::PlaceTextLeft("XYZ: %.3f / %.3f / %.3f", 1.0f, 1.0f, 1.0f);

            GUI::PlaceTextRight("Display: %ix%i", Global::GetWindow().GetWidth(), Global::GetWindow().GetHeight());

            GUI::PlaceTextRight("%s", Devices::GetGPUVersion().c_str());

            GUI::PlaceTextRight("%s", Devices::GetGLVersion().c_str());

            ImGui::End();

            ImGui::PopStyleColor();
        }
        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

        //////////////////////////////////////////////////////////////////////////////////////////////

        Global::GetWindow().SwapBuffers();

        //////////////////////////////////////////////////////////////////////////////////////////////

        Input::Flush(Global::GetKeyboardInput(), Global::GetMouseInput());

        //////////////////////////////////////////////////////////////////////////////////////////////
    }

    return 0;

    //////////////////////////////////////////////////////////////////////////////////////////////
}