#include <iostream>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


int main ()
{
        // -------------------------
        // GLFW
        // -------------------------

        if (!glfwInit())
        {
                std::cerr << "Failed to initialize GLFW\n";
                glfwTerminate();
                return 1;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow* window = glfwCreateWindow(1280, 720, "My ImGui Project", nullptr, nullptr);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);

        // -------------------------
        // Dear ImGui
        // -------------------------

        IMGUI_CHECKVERSION();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        ImGui::CreateContext();

        ImGui::StyleColorsDark();

        // -------------------------
        // ImGui Backends
        // -------------------------

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        // -------------------------
        // Main Loop
        // -------------------------

        
        char name[64] = "PlayerOne";
        int age = 100;
        float level = 1.0f;
        bool isAlive = true;
        

        while (!glfwWindowShouldClose(window))
        {
                glfwPollEvents();

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // -------------------------// GUI // ------------------------- //

                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
                ImGui::Begin(
                        "Counter",
                        nullptr,
                        ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove
                        );

                // ---- Elements ---- //



                ImGui::InputText("Name", name, IM_ARRAYSIZE(name));
                ImGui::DragInt("Age", &age, 1.0f, 0, 200);
                ImGui::DragFloat("Level", &level, 0.5f, 0.0f, 100.0f);

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();


                if (ImGui::Button("Level Up"))
                {
                        level++;
                }
                ImGui::SameLine();
                if (ImGui::Button("Level Down"))
                {
                        level--;
                }
                ImGui::SameLine();
                if (ImGui::Button("Reset Level"))
                {
                        level = 0;
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                
                ImGui::Checkbox("isAlive", &isAlive);
                if (isAlive)
                {
                        ImGui::Text("Player is alive");
                }
                else
                {
                        ImGui::Text("Player is dead");
                }

                if (ImGui::Button("Kill Player"))
                {
                        isAlive = false;
                }
                ImGui::SameLine();
                if (ImGui::Button("Revive Player"))
                {
                        isAlive = true;
                }
                

                // -------------------------// Render // ------------------------- //

                ImGui::End();

                ImGui::Render();
                
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                glfwSwapBuffers(window);

        }

        // -------------------------
        // Cleanup
        // -------------------------

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(window);
        glfwTerminate();

        return 0;
}