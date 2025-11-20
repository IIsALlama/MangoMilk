
#include "main.h"

const ImVec4 COLOUR_ERROR = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
const ImVec4 COLOUR_WARNING = ImVec4(1.0f, 1.0f, 0.8f, 1.0f);
const ImVec4 COLOUR_MESSAGE = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

GLFWwindow* window;
Entity* selectedEntity = NULL;

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

void window_inspector()
{
    ImGui::Begin("Inspector");

    if (selectedEntity != NULL) {
        ImGui::Text(selectedEntity->name);

        vector<Component*> components = selectedEntity->GetAllComponents();
        for (size_t i = 0; i < components.size(); i++)
        {
            const char* componentName = components[i]->GetName();
            ImGui::BeginChild(componentName);
            ImGui::Text(componentName);


            ImGui::EndChild();
        }
    }

    ImGui::End();
}

void window_hierarchy()
{
    ImGui::Begin("Hierarchy");

    ImGui::BeginChild("Scrolling");
    
    vector<Entity*> entities = GameManager::GetEntities();
    for (size_t i = 0; i < entities.size(); i++)
    {
        Entity* entity = entities[i];
        if (ImGui::Button(entity->name, ImVec2(200, 20))) {
            selectedEntity = entity;
        }
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
            ImGui::TextColored(COLOUR_MESSAGE, Debug::GetLog(n)->msg, n);
            break;
        case Debug::LogType::Warning:
            ImGui::TextColored(COLOUR_WARNING, Debug::GetLog(n)->msg, n);
            break;
        case Debug::LogType::Error:
            ImGui::TextColored(COLOUR_ERROR, Debug::GetLog(n)->msg, n);
            break;
        }
    }
    ImGui::EndChild();

    ImGui::End();
}

void window_game_view() 
{
    ImGui::Begin("Game View");

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

int main()
{
    //Initialize
    if (Initialize() == -1) {
        return -1;
    }

    Debug::Log("Test log");
    Debug::LogWarning("Test Warning");
    Debug::LogError("Test Error");

    Entity* e1 = new Entity("Big Square");
    Entity* e2 = new Entity("Small Square");
    e2->transform->scale = Vector2(0.2f, 0.2f);
    e2->transform->position = Vector2(0.7f, 0.5f);

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
        GameRender::Render ();

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