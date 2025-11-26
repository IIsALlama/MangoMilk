
#include "hierarchy.h"

#include "game_manager.h"
#include "debugging.h"

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
        std::vector<Entity*> shownChildren;
        
        Entity* ShowEntitysRecursive(Entity* e) {
            Entity* selectedEntity = nullptr;

            ImGui::PushID(id++);
            if (ImGui::Button(e->name, ImVec2(200, 20))) {
                selectedEntity = e;
            }
            ImGui::PopID();

            if (ImGui::BeginDragDropSource()) {
                ImGui::SetDragDropPayload("EntityDragDrop", &e, sizeof(Entity*));
                ImGui::Text(e->name);
                ImGui::EndDragDropSource();
            }

            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* dragDropData = ImGui::AcceptDragDropPayload("EntityDragDrop")) {
                    Entity* draggedEntity = *static_cast<Entity* const*>(dragDropData->Data);
                    e->AddChild(draggedEntity);
                }
                ImGui::EndDragDropTarget();
            }
            
            ImGui::Indent();
            std::vector<Entity*> children = e->GetChildren();
            for (size_t i = 0; i < children.size(); i++)
            {
                selectedEntity = ShowEntitysRecursive(children[i]);
                shownChildren.push_back(children[i]);
            }
            ImGui::Unindent();

            return selectedEntity;
        }

        void DropTarget() {
            //DRAG DROP TARGET
            ImGui::PushID(id++);
            float spacing = ImGui::GetStyle().ItemSpacing.y;
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - spacing + 2);
            ImGui::InvisibleButton("DropTarget", ImVec2(-1, 5));
            ImGui::PopID();

            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* dragDropData = ImGui::AcceptDragDropPayload("EntityDragDrop")) {
                    Entity* draggedEntity = *static_cast<Entity* const*>(dragDropData->Data);
                    if (draggedEntity->parent != nullptr) {
                        draggedEntity->parent->RemoveChild(draggedEntity);
                    }
                }
                ImGui::EndDragDropTarget();
            }
        }

        Entity* Window()
        {
            id = 0;
            shownChildren.clear();
            Entity* selectedEntity = nullptr;

            ImGui::Begin("Hierarchy"); //IMGUI WINDOW

            ImGui::BeginChild("Scrolling"); //IMGUI CHILD

            //Entity List
            std::vector<Entity*> entities = GameManager::GetEntities();
            for (size_t i = 0; i < entities.size(); i++)
            {
                Entity* entity = entities[i];

                if (std::find(shownChildren.begin(), shownChildren.end(), entity) != shownChildren.end()) {
                    continue;
                }

                DropTarget();

                ShowEntitysRecursive(entities[i]);
            }
            DropTarget();
            GameManager::SetEntities(entities);

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