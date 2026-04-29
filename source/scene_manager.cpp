#include "scene_manager.h"

#include "game_manager.h"

#include <vector>
#include <iostream>
#include <fstream>

#include "json.hpp";
#include "neat/Reflection.h"
using json = nlohmann::json;

import Entity;

namespace MangoMilk {
	namespace SceneManager{
		std::vector<Scene*> loadedScenes;
		Scene* currentScene;

		void Initialize() {
			Scene* scene = NewScene();
			currentScene = scene;
		}

		void OpenScene(int sceneIndex) {
			SaveCurrentScene();
			currentScene = loadedScenes[sceneIndex];
			GameManager::SetEntities(currentScene->entities);
		}

		Scene* NewScene() {
			Scene* newScene = new Scene();
			loadedScenes.push_back(newScene);

			return newScene;
		}

		std::vector<Scene*> GetScenes() {
			return loadedScenes;
		}


		json Serialize(Neat::AnyPtr object) {
			if (object.type_id == Neat::get_id<int>())
			{
				return *static_cast<int*>(object.value_ptr);
			}
			else if (object.type_id == Neat::get_id<float>())
			{
				return *static_cast<float*>(object.value_ptr);
			}
			else if (object.type_id == Neat::get_id<double>())
			{
				return *static_cast<double*>(object.value_ptr);
			}
			else if (object.type_id == Neat::get_id<std::string>())
			{
				return *static_cast<std::string*>(object.value_ptr);
			}
			else
			{
				return json{};
			}
		}

		void Deserialise(Neat::AnyPtr object, const Neat::Field& field, const json& data)
		{
			if (data.is_null())
			{
				return;
			}

			Neat::Any value{};

			if (field.type == Neat::get_id<int>())
			{
				value = data.get<int>();
			}
			else if (field.type == Neat::get_id<bool>())
			{
				value = data.get<bool>();
			}
			else if (field.type == Neat::get_id<float>())
			{
				value = data.get<float>();
			}
			else if (field.type == Neat::get_id<double>())
			{
				value = data.get<double>();
			}
			else if (field.type == Neat::get_id<std::string>())
			{
				value = data.get<std::string>();
			}
			//else if (data.is_array()) {
			//    std::vector<std::any> vec;
			//    for (const auto& element : data) {
			//        vec.push_back(jsonToAny(element));
			//    }
			//    return vec;
			//}
			//else if (data.is_object()) {
			//    std::map<std::string, std::any> obj;
			//    for (auto it = data.begin(); it != data.end(); ++it) {
			//        obj[it.key()] = jsonToAny(it.value());
			//    }
			//    return obj;
			//}

			field.set_value(object, value);
		}

		void SaveCurrentScene() {
			currentScene->entities = GameManager::GetEntities();

			//const Neat::Type* type = Neat::get_type<Entity>();
			//Neat::AnyPtr my_data_serialisation_ptr{ &currentScene->entities[0], type->id };

			/*json field_data{};
			for (const auto& field : type->fields)
			{
				field_data.emplace(field.name, Serialize(field.get_address(my_data_serialisation_ptr)));
			}

			std::ofstream o("test.json");
			o << std::setw(4) << field_data << std::endl;*/
		}
	}

}