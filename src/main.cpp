#include <iostream>

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include <algorithm>
#include <vector>

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

        std::string menuStatus = "";
        
        int level = 1;

        struct Item
        {
                std::string name;
                std::string type;
                int amount;
                bool equipped;
        };
        std::vector<Item> inventory =
        {
                {"Sword", "Weapon", 1, false},
                {"Potion", "Heal", 5, false},
                {"Shield", "Armor", 1, false},
                {"Bow", "Weapon", 1, false}
        };

        int selectedItem = -1;

        bool isProcessing = false;
        bool showPopup = true;
        bool showPopupID1 = false;

        int equippedItem = -1;
        
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

                
                

                ImGui::SetNextWindowPos(ImVec2(25.0f ,25.0f));
                ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x /2 - 25.0f - 12.5f, ImGui::GetIO().DisplaySize.y /2 - 25.0f - 12.5f));

                ImGui::Begin("Status");
                        ImGui::BeginChild("", ImVec2(50, 300));

                                ImGui::Text("Player Status");

                                ImGui::Text("Alive");
                                ImGui::Text("Difficulty");
                                ImGui::Text("Level : %.1f", level);

                        ImGui::EndChild();
                        ImGui::SameLine();
                        ImGui::BeginChild("", ImVec2(50, 300));

                                ImGui::Text("Actions");
                                ImGui::Button("Kill");
                                ImGui::Button("Resize");
                                ImGui::Button("Reset");

                        ImGui::EndChild();
                        ImGui::End();

                        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 + 12.5f, 25.0f));
                        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 25.0f - 12.5f, ImGui::GetIO().DisplaySize.y / 2 - 25.0f - 12.5f));

                        ImGui::Begin("Inventory");




                        
                        if (ImGui::BeginTable("InventoryTable", 3))
                        {

                                ImGui::TableSetupColumn("Item");
                                ImGui::TableSetupColumn("Type");
                                ImGui::TableSetupColumn("Amount");

                                ImGui::TableHeadersRow();

                                for (int i = 0; i < (int)inventory.size(); i++)
                                {
                                        ImGui::TableNextRow();
                                        bool selected = (selectedItem == i);
                                        ImGui::TableNextColumn();
                                        // ImGui::Text("%s", inventory[i].name.c_str());
                                        if (ImGui::Selectable(inventory[i].name.c_str(), selected, ImGuiSelectableFlags_SpanAllColumns))
                                        {
                                                selectedItem = i;
                                        }
                                        if (ImGui::IsItemHovered())
                                        {
                                                ImGui::BeginTooltip();
                                                ImGui::Text("%s", inventory[i].name.c_str());
                                                ImGui::Text("%s", inventory[i].type.c_str());
                                                ImGui::Text("%d", inventory[i].amount);
                                                ImGui::EndTooltip();
                                        }
                                        if (ImGui::BeginPopupContextItem())
                                        {
                                                if (ImGui::MenuItem("Equip"))
                                                {
                                                        selectedItem = i;
                                                        if (equippedItem >= 0)
                                                        {
                                                                inventory[equippedItem].equipped = false;
                                                        }
                                                        equippedItem = selectedItem;
                                                        inventory[selectedItem].equipped = true;
                                                }

                                                if (ImGui::MenuItem("Inspect"))
                                                {
                                                        selectedItem = i;
                                                }

                                                if (ImGui::MenuItem("Drop"))
                                                {
                                                        selectedItem = i;
                                                        showPopupID1 = true;
                                                }

                                                if (ImGui::Button("hello"))
                                                {
                                                        selectedItem = i;
                                                }

                                                ImGui::EndPopup();
                                        }

                                        ImGui::TableNextColumn();
                                        ImGui::Text("%s", inventory[i].type.c_str());

                                        ImGui::TableNextColumn();
                                        ImGui::Text("%d", inventory[i].amount);

                                }
                                ImGui::EndTable();
                        }

                        
                        if (selectedItem >= 0)
                        {
                                ImGui::Text("Selected Item : ");
                                ImGui::Text("Name: %s", inventory[selectedItem].name.c_str());
                                ImGui::Text("Type: %s", inventory[selectedItem].type.c_str());
                                ImGui::Text("Amount: %d", inventory[selectedItem].amount);
                                ImGui::Text("Status: %s", (inventory[selectedItem].equipped) ? "Equipped" : "Not Equipped");

                                if (ImGui::Button("Equip"))
                                {
                                        if (equippedItem >= 0)
                                        {
                                                inventory[equippedItem].equipped = false;
                                        }
                                        equippedItem = selectedItem;
                                        inventory[selectedItem].equipped = true;
                                }
                                ImGui::SameLine();
                                if (ImGui::Button("UnEquip"))
                                {
                                        if (selectedItem == equippedItem)
                                        {
                                                inventory[selectedItem].equipped = false;
                                                equippedItem = -1;
                                        }
                                }
                                ImGui::SameLine();
                                if (ImGui::Button("Drop"))
                                {
                                        ImGui::OpenPopup("Drop Confirm");
                                        if (!showPopup)
                                        {
                                                std::cout << "random function";
                                        }
                                }
                        }
                        else
                        {
                                ImGui::Text("No Item Selected");
                        }

                        

                        if (showPopupID1)
                        {
                                ImGui::OpenPopup("Drop Confirm");
                        }
                        if (showPopup && ImGui::BeginPopupModal("Drop Confirm"))
                        {
                                ImGui::Text("are you sure ?");

                                ImGui::BeginDisabled(isProcessing);
                                if (ImGui::Button("yes"))
                                {
                                        isProcessing = true;
                                        if (equippedItem == selectedItem)
                                        {
                                                equippedItem = -1;
                                        }
                                        else if (equippedItem > selectedItem)
                                        {
                                                equippedItem--;
                                        }
                                        inventory.erase(inventory.begin() + selectedItem);

                                        isProcessing = false;

                                        showPopup = false;
                                        ImGui::CloseCurrentPopup();
                                }
                                ImGui::SameLine();
                                if (ImGui::Button("no"))
                                {
                                        showPopup = false;
                                        ImGui::CloseCurrentPopup();
                                }
                                ImGui::EndDisabled();

                                showPopupID1 = false;
                                ImGui::EndPopup();
                        }
                        else 
                        {
                                showPopupID1 = false;
                        }

                        ImGui::End();

                        ImGui::SetNextWindowPos(ImVec2(25.0f, ImGui::GetIO().DisplaySize.y / 2 + 12.5f));
                        ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - 25.0f - 25.0f, ImGui::GetIO().DisplaySize.y / 2 - 25.0f - 12.5f));

                        ImGui::Begin("Status1");

                        ImGui::Text("Alive");
                        ImGui::Text("Difficulty");
                        ImGui::Text("Menu Status");

                ImGui::End();




                ImGui::SetNextWindowSize(ImVec2(500, 300));
                ImGui::Begin("Input Debugger");

                ImGui::Text("Mouse X: %.1f", io.MousePos.x);
                ImGui::Text("Mouse Y: %.1f", io.MousePos.y);


                ImGui::Text("-> ");
                ImGui::SameLine();
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                        ImGui::Text("IsMouseClicked");
                }
                else
                {
                        ImGui::Text("");
                }

                ImGui::Text("-> ");
                ImGui::SameLine();
                if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
                {
                        ImGui::Text("IsMouseDown");
                }
                else
                {
                        ImGui::Text("");
                }

                ImGui::Text("-> ");
                ImGui::SameLine();
                if (ImGui::IsKeyPressed(ImGuiKey_Space))
                {
                        ImGui::Text("IsKeyPressed");
                }
                else
                {
                        ImGui::Text("");
                }

                ImGui::Text("-> ");
                ImGui::SameLine();
                if (ImGui::IsKeyDown(ImGuiKey_Space))
                {
                        ImGui::Text("IsKeyDown");
                }
                else
                {
                        
                        ImGui::Text("");
                }

                


                if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_S))
                {
                        ImGui::Text("Save");
                }
                if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_Z))
                {
                        ImGui::Text("Undo");
                }
                if (ImGui::IsKeyPressed(ImGuiKey_Escape))
                {
                        ImGui::Text("Escape");
                }


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