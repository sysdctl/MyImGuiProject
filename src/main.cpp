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
                
                void addLevel (int i)
                {
                        level += i;
                }

                void removeLevel (int i)
                {
                        level -= i;
                }

                void resetLevel ()
                {
                        level = 0;
                }

                int getLevel () const
                {
                        return level;
                }
};

class PlayerController
{
        private:
                Player& player;
        public:
                PlayerController (Player& player)
                : player(player)
                {}

                void levelUp ()
                {
                        player.addLevel(1);
                }

                void levelDown ()
                {
                        player.removeLevel(1);
                }

                void reset ()
                {
                        player.resetLevel();
                }
};
namespace PlayerControllerGUI {
void addEventButton(const char* label, std::function<void()> event)
{
        if (ImGui::Button(label))
        {
                event();
        }
}
}
void myButton (const char* name, std::function<void()> callback)
{
        if (ImGui::Button(name))
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
        PlayerController playerController(player);

        
        std::function<void()> onLevelUp = [&playerController](){
                playerController.levelUp();
        };
        std::function<void()> onLevelDown = [&playerController](){
                playerController.levelDown();
        };
        std::function<void()> onReset = [&playerController](){
                playerController.reset();
        };
        
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
                        

                


                if (ImGui::Button("level up"))
                {
                        onLevelUp();
                }
                if (ImGui::Button("level down"))
                {
                        onLevelDown();
                }
                if (ImGui::Button("reset level"))
                {
                        onReset();
                }

                PlayerControllerGUI::addEventButton("level up2", onLevelUp);
                PlayerControllerGUI::addEventButton("level down2", onLevelDown);
                PlayerControllerGUI::addEventButton("reset level2", onReset);

                PlayerControllerGUI::addEventButton("level up3", [&playerController]{
                        playerController.levelUp();
                });
                PlayerControllerGUI::addEventButton("level down3", [&playerController]{
                        playerController.levelDown();
                });
                PlayerControllerGUI::addEventButton("reset level3", [&playerController]{
                        playerController.reset();
                });

                if (ImGui::Button("level up4"))
                {
                        playerController.levelUp();
                }
                if (ImGui::Button("level down4"))
                {
                        playerController.levelDown();
                }
                if (ImGui::Button("reset level4"))
                {
                        playerController.reset();
                }

                ImGui::Text("%d", player.getLevel());





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