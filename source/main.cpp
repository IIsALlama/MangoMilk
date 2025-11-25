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

using namespace MangoMilk;
using namespace Neat;
using namespace std;

import MangoMilk;

import Transform;
import Component;
import Entity;
import SpriteRenderer;

const ImVec4 COLOUR_ERROR = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
const ImVec4 COLOUR_WARNING = ImVec4(1.0f, 1.0f, 0.8f, 1.0f);
const ImVec4 COLOUR_MESSAGE = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

Colour colour_blue = Colour(0.0f, 0.0f, 1.0f);
Colour colour_red = Colour(1.0f, 0.0f, 0.0f);
Colour colour_green = Colour(0.0f, 1.0f, 0.0f);

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

void window_hierarchy()
{
    ImGui::Begin("Hierarchy");

    ImGui::BeginChild("Scrolling");
    
    vector<Entity*> entities = GameManager::GetEntities();
    int id = 0;
    for (size_t i = 0; i < entities.size(); i++)
    {
        Entity* entity = entities[i];

        ImGui::PushID(id);

        if (ImGui::Button(entity->name, ImVec2(200, 20))) {
            selectedEntity = entity;
        }

        ImGui::PopID();
        id++;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        ImGui::Text("Create New:");
        if (ImGui::MenuItem("Entity")) { GameManager::Instantiate(new Entity("New Entity")); };
        if (ImGui::MenuItem("Sprite")) { Entity* e = GameManager::Instantiate(new Entity("New Sprite")); e->AddComponent(new SpriteRenderer()); };
        ImGui::EndPopup();
    }

    ImGui::EndChild();


    ImGui::End();
}

void window_console()
{
    ImGui::Begin("Console");

    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < Debug::GetLogSize(); n++) {
        Debug::LogMessage* log = Debug::GetLog(n);
        switch (Debug::GetLog(n)->type)
        {
        default:
            break;
        case Debug::LogType::Message:
            ImGui::TextColored(COLOUR_MESSAGE, Debug::GetLog(n)->msg.c_str(), n);
            break;
        case Debug::LogType::Warning:
            ImGui::TextColored(COLOUR_WARNING, Debug::GetLog(n)->msg.c_str(), n);
            break;
        case Debug::LogType::Error:
            ImGui::TextColored(COLOUR_ERROR, Debug::GetLog(n)->msg.c_str(), n);
            break;
        }
    }
    ImGui::EndChild();

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

const Type* GetComponentType(MangoMilk::Component* component) {
    //Get name of component
    std::string fullComponentName = component->GetName();
    unsigned first = fullComponentName.find(" ");
    unsigned last = fullComponentName.find("[");
    std::string componentName = fullComponentName.substr(first + 1, last - first - 1);

    //Get reflection data
    const Type* type = Neat::get_type(componentName);

    //AnyPtr typePtr{ component, type->id };

    return type;
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
    SpriteRenderer* sp = new SpriteRenderer();
    sp->colour = colour_blue;
    e1->AddComponent(sp);
    Entity* e2 = GameManager::Instantiate(new Entity("Small Square"));
    e2->AddComponent(new SpriteRenderer());
    e2->transform->scale = Vector2(0.2f, 0.2f);
    e2->transform->position = Vector2(0.7f, 0.5f);

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
        //window_inspector();
        Inspector::Window(selectedEntity);
        window_hierarchy();
        window_console();
        
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