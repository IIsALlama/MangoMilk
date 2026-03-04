#include <fstream>
#include <thread>
#include <cassert>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "common.h"
#include "debugging.h"
#include "game_manager.h"
#include "game_render.h"
#include "inspector.h"
#include "hierarchy.h"

using namespace MangoMilk;
using namespace Neat;
using namespace std;

import MangoMilk;

import Transform;
import Component;
import Entity;
import SpriteRenderer;

Colour colour_blue = Colour(0.0f, 0.0f, 1.0f);
Colour colour_red = Colour(1.0f, 0.0f, 0.0f);
Colour colour_green = Colour(0.0f, 1.0f, 0.0f);
Colour colour_white = Colour(1.0f, 1.0f, 1.0f);

GLFWwindow* window;
Entity* selectedEntity = nullptr;

bool FileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int Initialize() // Initialize Libraries
{
    // Initialize GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // Create Window
    window = glfwCreateWindow(800, 600, "Mango Milk", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewInit();

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    //Input
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    //Style
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 10.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    //set_style_mango_milk();

    //Load default layout
    ImGui::LoadIniSettingsFromDisk("layout_default.ini");
    //Try to load gui settings
    ImGui::LoadIniSettingsFromDisk("layout.ini");
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    GameRender::Initialize();

    return 0;
}

void window_viewport()
{
    ImGuiIO io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize);
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    ImGui::Begin("Mango Milk");

    ImGui::End();
}

void window_assets() 
{
    ImGui::Begin("Assets");

    ImGui::End();
}

void OnPlay() {
    
}

void OnStop() {
    
}

void window_game_view() 
{
    ImGui::Begin("Game View", NULL, ImGuiWindowFlags_MenuBar);

    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;
    GameRender::Rescale(window_width, window_height);

    if (ImGui::Button("Play")) {
        OnPlay();
    }

    glViewport(0, 0, window_width, window_height);
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddImage(
        (void*)GameRender::outputTexture,
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + window_width, pos.y + window_height),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );


    ImGui::End();
}

void window_scene_view()
{
    ImGui::Begin("Scene View");

    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;
    GameRender::Rescale(window_width, window_height);

    glViewport(0, 0, window_width, window_height);
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddImage(
        (void*)GameRender::outputTexture,
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + window_width, pos.y + window_height),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );

    ImGui::End();
}

void window_menubar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Create")) {
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
            }
            if (ImGui::MenuItem("Save as..")) {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Settings")) {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

Entity* GetEntity(MangoMilk::Component* component) {
    return component->CastOwnerPtr<Entity>();
}

std::vector<const Type*> GetComponentTypes() {
    const Type* componentType = Neat::get_type<Component>();
    std::vector<const Type*> componentTypes;
    auto reflectedTypes = Neat::get_types();
    for (size_t i = 0; i < reflectedTypes.size(); i++)
    {
        std::vector<BaseClass> bases = reflectedTypes[i].bases;
        for (size_t n = 0; n < bases.size(); n++)
        {
            if (bases[n].base_id == componentType->id) {
                Debug::Log(reflectedTypes[i].name);
                componentTypes.push_back(&reflectedTypes[i]);
            }
        }
    }
    return componentTypes;
}

int main()
{
    //Initialize
    if (Initialize() == -1) {
        return -1;
    }

    Debug::Log("Test log");
    Debug::LogWarning("Test Warning");
    Debug::LogError("Test Error");

    Entity* e1 = GameManager::Instantiate(new Entity("Big Square"));
    SpriteRenderer* sp = new SpriteRenderer("mangomilk");
    sp->colour = colour_white;
    e1->AddComponent(sp);
    e1->transform->scale = Vector2(2.0f, 2.0f);
    Entity* e2 = GameManager::Instantiate(new Entity("Small Square"));
    e2->AddComponent(new SpriteRenderer("mangomilk"));
    e2->transform->scale = Vector2(0.2f, 0.2f);
    e2->transform->position = Vector2(0.7f, 0.5f);

    e1->transform->AddChild(e2->transform);

    GetComponentTypes();
    // Render Loop
    while (!glfwWindowShouldClose(window))
    {
        // Create Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport();

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        // Window GUIs
        //window_viewport();
        window_menubar();

        window_game_view();
        window_scene_view();

        window_assets();
        Debug::Window();

        Inspector::Window(selectedEntity);
        Entity* returnEntity = Hierarchy::Window();
        if (returnEntity != nullptr) selectedEntity = returnEntity;
        
        // Render
        ImGui::Render();

        GameManager::GameLoop();

        //Debug::Log("AAQAA");

        // End Of Render Loop
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui::SaveIniSettingsToDisk("layout.ini");

    //Terminate
    GameRender::Terminate();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}