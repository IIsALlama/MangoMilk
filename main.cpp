
#include "main.h"
#include "style.h"
#include "game_render.h"

GLFWwindow* window;

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

int initialize() // Initialize Libraries
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
    game_render_initialize();

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

void window_inspector()
{
    ImGui::Begin("Inspector");

    ImGui::End();
}

void window_hierarchy()
{
    ImGui::Begin("Hierarchy");

    ImGui::End();
}

void window_console()
{
    ImGui::Begin("Console");

    ImGui::End();
}

void window_game_view() 
{
    ImGui::Begin("Game View");

    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;
    game_render_rescale(window_width, window_height);

    glViewport(0, 0, window_width, window_height);
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddImage(
        (void*)game_render_texture,
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
    game_render_rescale(window_width, window_height);

    glViewport(0, 0, window_width, window_height);
    ImVec2 pos = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddImage(
        (void*)game_render_texture,
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + window_width, pos.y + window_height),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );

    ImGui::End();
}

int main()
{
    //Initialize
    if (initialize() == -1) {
        return -1;
    }

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {
        // Input handling
        glfwPollEvents();

        // Create Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport();

        glClear(GL_COLOR_BUFFER_BIT);

        // Window GUIs
        //window_viewport();

        window_game_view();
        window_scene_view();

        window_assets();
        window_inspector();
        window_hierarchy();
        window_console();
        
        // Render
        ImGui::Render();
        game_render();

        // End Of Render Loop
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui::SaveIniSettingsToDisk("layout.ini");

    //Terminate
    game_render_terminate();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}