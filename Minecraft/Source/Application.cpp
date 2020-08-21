#include "Input.h"
#include "Console.h"
#include "Devices.h"
#include "GUI/GUI.h"
#include "Global.h"
#include "3D/Object/Object3D.h"
#include "3D/Scene/Camera.h"

#include <glew.h>
#include <glfw3.h>
#include <chrono>
#include <memory>

#include "Vendor/glm/glm.hpp"
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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    bool shouldDisplayDebugInfo = true;

    //////////////////////////////////////////////////////////////////////////////////////////////
    
    std::unique_ptr<Object3D> cube = std::make_unique<Object3D>("Resources/Block.obj", "Resources/Basic", "Resources/Basic.png");
    std::unique_ptr<Camera> camera = std::make_unique<Camera>();
    camera->SetRotation(glm::vec3(45.0f, 45.0f, 0.0f));
    glfwSetInputMode(Global::GetWindow().GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //////////////////////////////////////////////////////////////////////////////////////////////

    while (!Global::GetWindow().ShouldCloseWindow())
    {
        //////////////////////////////////////////////////////////////////////////////////////////////
        currentTime = std::chrono::high_resolution_clock::now();
        auto deltaTimeNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime);
        lastTime = currentTime;
        double deltaTime = deltaTimeNanoseconds.count() / 1000000000.0;
        double deltaTimeWithTimeFactor = deltaTime * timeConstant;
        //////////////////////////////////////////////////////////////////////////////////////////////
        Global::GetWindow().PollEvents();
        Input::ProcessEvents(Global::GetKeyboardInput(), Global::GetMouseInput());
        //////////////////////////////////////////////////////////////////////////////////////////////


        // PROCESS INPUT
        if (Global::GetKeyboardInput().m_KeysPressed[MC_KEY_F3]) {
            shouldDisplayDebugInfo = !shouldDisplayDebugInfo;
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_RIGHT_CONTROL] && Global::GetKeyboardInput().m_KeysHeld[MC_KEY_0]) {
            Global::GetConfig().Save();
        }
        if (Global::GetKeyboardInput().m_KeysPressed[MC_KEY_LEFT_CONTROL]) {
            glfwSetInputMode(Global::GetWindow().GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        if (Global::GetKeyboardInput().m_KeysReleased[MC_KEY_LEFT_CONTROL]) {
            glfwSetInputMode(Global::GetWindow().GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_W] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_W]) {
            camera->MoveForward(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_A] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_A]) {
            camera->StrafeLeft(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_S] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_S]) {
            camera->MoveBackward(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_D] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_D]) {
            camera->StrafeRight(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_LEFT_SHIFT] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_LEFT_SHIFT]) {
            camera->MoveDown(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_SPACE] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_SPACE]) {
            camera->MoveUp(deltaTime);
        }
        //camera->SetUpDirection(glm::vec3(0.0f, -1.0f, 0.0f));
        Console::Info("Player rotation (%f, %f, %f)", camera->GetRotation().x, camera->GetRotation().y, camera->GetRotation().z);
        camera->LookAtMouse(Global::GetConfig().GetMouseSensitivity(), Global::GetMouseInput().m_MouseX, Global::GetMouseInput().m_MouseY);
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_E]) {
            camera->LookAt(glm::vec3(0.0f, 0.0f, -5.0f));
        }

        //////////////////////////////////////////////////////////////////////////////////////////////
        Global::GetWindow().ClearBuffer();
        //////////////////////////////////////////////////////////////////////////////////////////////


        // RENDER 3D
        cube->SetTranslation(glm::vec3(0.0f, 0.0f, -5.0f));
        cube->Draw(camera->GetProjectionMatrix(), camera->GetViewMatrix(), glm::mat4(1.0f));


        //////////////////////////////////////////////////////////////////////////////////////////////


        // RENDER GUI
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
        Global::GetMesh3DManager().Cleanup();
        Global::GetTextureManager().Cleanup();
        Global::GetShaderManager().Cleanup();
        //////////////////////////////////////////////////////////////////////////////////////////////
    }

    return 0;

    //////////////////////////////////////////////////////////////////////////////////////////////
}