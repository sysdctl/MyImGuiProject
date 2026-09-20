#include <iostream>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <algorithm>

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

        int selectedClass = 0;
        const char* classes[] = {
                "Warrior",
                "Mage",
                "Archer",
                "Rogue"
        };

        int difficulty = 0;
        
        float playerColor[] = { 1.0f, 0.0f, 0.0f };
        float playerColor4[] = { 1.0f, 0.0f, 0.0f, 1.0f };

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
                ImGui::ListBox("Class", &selectedClass, classes, IM_ARRAYSIZE(classes), 3);

                switch (selectedClass)
                {
                        case 0:
                                ImGui::Text("Class: Warrior");
                                ImGui::Text("Ability: Strong Attack");
                                break;
                        case 1:
                                ImGui::Text("Class: Mage");
                                ImGui::Text("Ability: Fireball");
                                break;
                        case 2:
                                ImGui::Text("Class: Archer");
                                ImGui::Text("Ability: Long Range Attack");
                                break;
                        case 3:
                                ImGui::Text("Class: Rogue");
                                ImGui::Text("Ability: Fast Attack");
                                break;
                }       

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                switch (difficulty)
                {
                        case 0:
                                ImGui::Text("Difficulty : Easy");
                                break;
                        case 1:
                                ImGui::Text("Difficulty : Normal");
                                break;
                        case 2:
                                ImGui::Text("Difficulty : Hard");
                                break;
                }

                ImGui::RadioButton("Easy", &difficulty, 0);
                ImGui::SameLine();
                ImGui::RadioButton("Normal", &difficulty, 1);
                ImGui::SameLine();
                ImGui::RadioButton("Hard", &difficulty, 2);

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

                level = std::clamp(level, 0.0f, 100.0f);
                ImGui::Text("Level Progress: %.1f%%", level);
                ImGui::ProgressBar(level / 100.0f);

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

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::ColorEdit3("Player Color", playerColor);
                ImGui::ColorEdit4("Player Color4", playerColor4);

                ImGui::Spacing();

                ImVec4 playerColor4Vec(playerColor4[0], playerColor4[1], playerColor4[2], playerColor4[3]);
                ImGui::PushStyleColor(ImGuiCol_Button, playerColor4Vec);
                if (ImGui::Button("Attack"))
                {
                        ImGui::Text("Attack!");
                }
                ImGui::PopStyleColor();
                ImGui::PushStyleColor(ImGuiCol_Text, playerColor4Vec);

                ImGui::Text("Player Name: Hamed");
                ImGui::Text("Player is Ready!");

                ImGui::PopStyleColor();

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