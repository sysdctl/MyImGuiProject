#include <iostream>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <algorithm>

void SetupTheme()
{
        ImGuiStyle& style = ImGui::GetStyle();

        // Style
        style.WindowRounding = 10.0f;
        style.FrameRounding = 5.0f;
        style.WindowPadding = ImVec2(15.0f, 15.0f);
        style.FramePadding = ImVec2(8.0f, 6.0f);
        style.ItemSpacing = ImVec2(8.0f, 10.0f);

        // Colors
        style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1804f, 0.1804f, 0.1804f, 1.0f);

        style.Colors[ImGuiCol_Text] = ImVec4(0.6863f, 0.6863f, 0.6941f, 1.0f);

        style.Colors[ImGuiCol_Button] = ImVec4(0.2373f, 0.2373f, 0.2451f, 1.0f);

        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.3373f, 0.3373f, 0.3451f, 1.0f);

        style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.2073f, 0.2073f, 0.2051f, 1.0f);

        style.Colors[ImGuiCol_Border] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

        style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1176f, 0.1176f, 0.1176f, 1.0f);
}

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
        SetupTheme();

        std::string menuStatus = "";


        while (!glfwWindowShouldClose(window))
        {
                glfwPollEvents();

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // -------------------------// GUI // ------------------------- //

                // ---- MenuBar ---- //

                if (ImGui::BeginMainMenuBar())
                {
                        if (ImGui::BeginMenu("File"))
                        {
                                if (ImGui::MenuItem("New"))
                                {
                                        menuStatus = "New";
                                }
                                if (ImGui::MenuItem("Save"))
                                {
                                        menuStatus = "Save";
                                }
                                if (ImGui::MenuItem("Exit"))
                                {
                                        menuStatus = "Exit";
                                }
                                ImGui::EndMenu();
                        }
                        if (ImGui::BeginMenu("Player"))
                        {
                                if (ImGui::MenuItem("Level Up"))
                                {
                                        menuStatus = "Level Up";
                                }
                                if (ImGui::MenuItem("Level Down"))
                                {
                                        menuStatus = "Level Down";
                                }
                                if (ImGui::MenuItem("Reset"))
                                {
                                        menuStatus = "Reset";
                                }
                                ImGui::EndMenu();
                        }
                        if (ImGui::BeginMenu("Help"))
                        {
                                if (ImGui::MenuItem("About"))
                                {
                                        menuStatus = "About";
                                }
                                ImGui::EndMenu();
                        }
                        ImGui::EndMainMenuBar();
                }

                ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()));
                ImGui::SetNextWindowSize(ImVec2(
                        ImGui::GetIO().DisplaySize.x,
                        ImGui::GetIO().DisplaySize.y - ImGui::GetFrameHeight()
                ));
                
                ImGui::Begin(
                        "Counter",
                        nullptr,
                        ImGuiWindowFlags_NoTitleBar |
                        ImGuiWindowFlags_NoResize |
                        ImGuiWindowFlags_NoMove
                        );

                // ---- Elements ---- //






                        

                        ImGui::Text("Hello Player");
                        ImGui::Button("Attack");
                        ImGui::Text("%s", menuStatus.c_str());

                        

                




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