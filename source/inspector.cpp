#include "inspector.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

import Component;
import Transform;
import SpriteRenderer;
import Entity;

using namespace MangoMilk;
using namespace Neat;

namespace MangoMilk {
    namespace Inspector {
        int id = 0;

        void ShowField(const Field* field, AnyPtr typePtr) {

            Any value = field->get_value(typePtr);
            const char* label = field->name.c_str();

            ImGui::Text(label); //IMGUI TEXT Field name

            if (value.type_id() == get_id<int>()) { //INT
                int* intValue = value.value_ptr<int>();

                ImGui::PushID(id++);
                if (ImGui::InputInt(label, intValue)) {
                    field->set_value(typePtr, value);
                }
                ImGui::PopID();
            }
            else if (value.type_id() == get_id<float>()) { //FLOAT
                float* floatValue = value.value_ptr<float>();

                ImGui::PushID(id++);
                if (ImGui::InputFloat(label, floatValue)) {
                    field->set_value(typePtr, value);
                }
                ImGui::PopID();
            }
            else if (value.type_id() == get_id<Vector2>()) { //VECTOR2
                Vector2* vec2Value = value.value_ptr<Vector2>();

                ImGui::PushID(id++);
                if (ImGui::InputFloat("X", &vec2Value->x)) {
                    field->set_value(typePtr, value);
                }
                ImGui::PopID();

                ImGui::PushID(id++);
                if (ImGui::InputFloat("Y", &vec2Value->y)) {
                    field->set_value(typePtr, value);
                }
                ImGui::PopID();
            }
            else if (value.type_id() == get_id<Colour>()) { //COLOUR
                Colour* colValue = value.value_ptr<Colour>();

                ImGui::PushID(id++);
                if (ImGui::InputFloat("R", &colValue->r)) {
                    field->set_value(typePtr, value);
                }
                ImGui::PopID();

                ImGui::PushID(id++);
                if (ImGui::InputFloat("G", &colValue->g)) {
                    field->set_value(typePtr, value);
                }
                ImGui::PopID();

                ImGui::PushID(id++);
                if (ImGui::InputFloat("B", &colValue->b)) {
                    field->set_value(typePtr, value);
                }
                ImGui::PopID();
            }
            else { //UNSUPPORTED
                ImGui::Text("Unsupported Field Type.");
            }
        }

        void ShowComponent(Component* component) {

            ImGui::BeginGroup(); //IMGUI GROUP

            //Get name of component
            std::string fullComponentName = component->GetName();
            unsigned first = fullComponentName.find(" ");
            unsigned last = fullComponentName.find("[");
            std::string componentName = fullComponentName.substr(first + 1, last - first - 1);

            ImGui::Text(componentName.c_str()); //IMGUI TEXT Component name

            //Get reflection data
            const Type* type = Neat::get_type(componentName);
            AnyPtr typePtr{ component, type->id };

            //Show Fields
            for (size_t i = 0; i < type->fields.size(); i++)
            {
                ShowField(&type->fields[i], typePtr);
            }

            ImGui::EndGroup(); //IMGUI GROUP END

            ImGui::Dummy(ImVec2(0.0f, 10.0f)); //IMGUI SPACING
        }

        void Window(MangoMilk::Entity* selectedEntity)
        {
            ImGui::Begin("Inspector"); //IMGUI WINDOW
            id = 0;

            if (selectedEntity != nullptr) {
                ImGui::Text(selectedEntity->name); //IMGUI TEXT Entity name

                ImGui::Dummy(ImVec2(0.0f, 10.0f)); //IMGUI SPACING

                //Show Components
                std::vector<Component*> components = selectedEntity->GetAllComponents();
                for (size_t i = 0; i < components.size(); i++)
                {
                    ShowComponent(components[i]);
                }
            }

            ImGui::End(); //IMGUI END WINDOW
        }
    }

}
