
#include "hierarchy.h"

#include "game_manager.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

import SpriteRenderer;
import Entity;

using namespace MangoMilk;
using namespace Neat;

namespace MangoMilk {
    namespace Hierarchy {
        int id = 0;

        Entity* Window()
        {
            id = 0;
            Entity* selectedEntity = nullptr;

            ImGui::Begin("Hierarchy"); //IMGUI WINDOW

            ImGui::BeginChild("Scrolling"); //IMGUI CHILD

            //Entity List
            std::vector<Entity*> entities = GameManager::GetEntities();
            for (size_t i = 0; i < entities.size(); i++)
            {
                Entity* entity = entities[i];

                ImGui::PushID(id++);
                if (ImGui::Button(entity->name, ImVec2(200, 20))) {
                    selectedEntity = entity;
                }
                ImGui::PopID();
            }

            //Content Menu
            if (ImGui::BeginPopupContextWindow())
            {
                ImGui::Text("Create New:");
                if (ImGui::MenuItem("Entity")) { GameManager::Instantiate(new Entity("New Entity")); };
                if (ImGui::MenuItem("Sprite")) { Entity* e = GameManager::Instantiate(new Entity("New Sprite")); e->AddComponent(new SpriteRenderer()); };
                ImGui::EndPopup();
            }

            ImGui::EndChild(); //IMGUI END CHILD


            ImGui::End(); //IMGUI END WINDOW

            return selectedEntity;
        }

    }
}