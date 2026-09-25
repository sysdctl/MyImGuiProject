#include <iostream>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <algorithm>
#include <vector>
#include <functional>

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


class Player
{
        private:
                int level = 0;

        public:
                
                void levelUp ()
                {
                        level++;
                }

                void levelDown ()
                {
                        level--;
                }

                int getLevel () const
                {
                        return level;
                }
};


void myButton (const char* text, std::function<void()> callback)
{
        if (ImGui::Button(text))
        {
                callback();
        }
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

        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
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
        
        Player player;
        
        while (!glfwWindowShouldClose(window))
        {
                glfwPollEvents();

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // -------------------------// GUI // ------------------------- //

                ImGui::SetNextWindowPos(ImVec2(25.0f ,25.0f));
                ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x /2 - 25.0f - 12.5f, ImGui::GetIO().DisplaySize.y /2 - 25.0f - 12.5f));

                ImGui::Begin("lambda");
                        

                


                myButton("LevelUp", [&player](){
                        player.levelUp();
                });
                myButton("LevelDown", [&player](){
                        player.levelDown();
                });
                ImGui::Text("Level: %d", player.getLevel());






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