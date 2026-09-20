#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

int main ()
{
        ImGui::CreateContext();
        ImGui::NewFrame();
        ImGui::Begin("My First Window");

        ImGui::Text("Hello Dear ImGui!");

        ImGui::End();
        ImGui::Render();
        ImGui::DestroyContext();
}