#include "Input.h"
#include "Console.h"
#include "Devices.h"
#include "GUI/GUI.h"
#include "Global.h"
#include "Random.h"
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
    //////////////////////////////////////////////////////////////////////////////////////////////

    Global::GetWindow().GetCurrentScene().GetCurrentCamera().SetSkybox(std::make_unique<Object3D>("Resources/Skybox.obj", "Resources/Basic", "Resources/Skybox.png"));
    Global::GetWindow().GetCurrentScene().AddChunk(glm::ivec3(0, 0, 0));
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 64; y++) {
            for (int z = 0; z < 16; z++) {
                Global::GetWindow().GetCurrentScene().GetLastChunk().GetBlock(x, y, z)->SetMaterial(Material::Dirt);
            }
        }
    }
    Global::GetWindow().GetCurrentScene().AddChunk(glm::ivec3(0, 0, 1));
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 64; y++) {
            for (int z = 0; z < 16; z++) {
                Global::GetWindow().GetCurrentScene().GetLastChunk().GetBlock(x, y, z)->SetMaterial(Material::Dirt);
            }
        }
    }
    Global::GetWindow().GetCurrentScene().AddChunk(glm::ivec3(-1, 0, 0));
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 64; y++) {
            for (int z = 0; z < 16; z++) {
                Global::GetWindow().GetCurrentScene().GetLastChunk().GetBlock(x, y, z)->SetMaterial(Material::Dirt);
            }
        }
    }
    Global::GetWindow().GetCurrentScene().AddChunk(glm::ivec3(-1, 0, 1));
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 64; y++) {
            for (int z = 0; z < 16; z++) {
                Global::GetWindow().GetCurrentScene().GetLastChunk().GetBlock(x, y, z)->SetMaterial(Material::Dirt);
            }
        }
    }
    Global::GetWindow().GetCurrentScene().AddChunk(glm::ivec3(1, 0, 0));
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 64; y++) {
            for (int z = 0; z < 16; z++) {
                Global::GetWindow().GetCurrentScene().GetLastChunk().GetBlock(x, y, z)->SetMaterial(Material::Dirt);
            }
        }
    }
    Global::GetWindow().GetCurrentScene().AddChunk(glm::ivec3(1, 0, 1));
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 64; y++) {
            for (int z = 0; z < 16; z++) {
                Global::GetWindow().GetCurrentScene().GetLastChunk().GetBlock(x, y, z)->SetMaterial(Material::Dirt);
            }
        }
    }
    Global::GetWindow().GetCurrentScene().GetCurrentCamera().SetTranslation(glm::vec3(0.0f, 64.0f, 0.0f));
    //Global::GetWindow().GetCurrentScene().AddEntity("Resources/Steve.obj", "Resources/Basic", "Resources/Steve.png", 0, glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    //Global::GetWindow().GetCurrentScene().AddEntity("Resources/Sphere.obj", "Resources/Basic", "Resources/Basic.png", 0, glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    Global::GetWindow().GetCurrentScene().AddEntity("Resources/AnimatedCube/AnimatedCube.obj", "Resources/Basic", "Resources/White.png", 48, glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    Global::GetWindow().GetCurrentScene().GetLastEntity().SetIsAnimating(true);

    //////////////////////////////////////////////////////////////////////////////////////////////

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
        Global::GetWindow().ClearBuffer();
        //////////////////////////////////////////////////////////////////////////////////////////////
        Scene& scene = Global::GetWindow().GetCurrentScene();
        Camera& camera = scene.GetCurrentCamera();
        //////////////////////////////////////////////////////////////////////////////////////////////


        // PROCESS INPUT
        if (Global::GetKeyboardInput().m_KeysPressed[MC_KEY_F3]) {
            Global::GetWindow().GetGUI().ToggleShouldDisplayDebugInfo();
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_RIGHT_CONTROL] && Global::GetKeyboardInput().m_KeysHeld[MC_KEY_0]) {
            Global::GetConfig().Save();
        }
        if (Global::GetKeyboardInput().m_KeysPressed[MC_KEY_LEFT_CONTROL]) {
            glfwSetInputMode(Global::GetWindow().GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            Global::GetMouseInput().m_ShouldReceiveInput = false;
        }
        if (Global::GetKeyboardInput().m_KeysReleased[MC_KEY_LEFT_CONTROL]) {
            Global::GetMouseInput().m_ShouldReceiveInput = true;
            camera.SetWasUsedYet(false);
            glfwSetInputMode(Global::GetWindow().GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_W] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_W]) {
            camera.MoveForward(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_A] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_A]) {
            camera.StrafeLeft(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_S] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_S]) {
            camera.MoveBackward(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_D] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_D]) {
            camera.StrafeRight(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_LEFT_SHIFT] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_LEFT_SHIFT]) {
            camera.MoveDown(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_SPACE] || Global::GetKeyboardInput().m_KeysPressed[MC_KEY_SPACE]) {
            camera.MoveUp(deltaTime);
        }
        if (Global::GetKeyboardInput().m_KeysHeld[MC_KEY_T]) {
            Global::GetWindow().GetCurrentScene().GetLastEntity().SetTranslation(glm::vec3(0.0f, 70.0f, 0.0f));
            Global::GetWindow().GetCurrentScene().GetLastEntity().SetVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
        }
        if (Global::GetMouseInput().m_MouseMoved) {
            camera.LookAtMouse(Global::GetConfig().GetMouseSensitivity(), Global::GetMouseInput().m_MouseX, Global::GetMouseInput().m_MouseY);
        }


        //////////////////////////////////////////////////////////////////////////////////////////////


        Global::GetWindow().GetCurrentScene().Update(deltaTimeWithTimeFactor);


        //////////////////////////////////////////////////////////////////////////////////////////////


        // RENDER 3D
        Global::GetWindow().GetCurrentScene().Draw();


        //////////////////////////////////////////////////////////////////////////////////////////////


        // RENDER GUI
        Global::GetWindow().GetGUI().Begin();

        Global::GetWindow().GetGUI().DisplayDebugInfo();
        Global::GetWindow().GetGUI().DisplayInventory();
        Global::GetWindow().GetGUI().DisplayMenu();

        Global::GetWindow().GetGUI().End();


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