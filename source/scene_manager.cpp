#include "scene_manager.h"

#include "game_manager.h"

#include <vector>

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

		void SaveCurrentScene() {
			currentScene->entities = GameManager::GetEntities();
		}

		Scene* NewScene() {
			Scene* newScene = new Scene();
			loadedScenes.push_back(newScene);

			return newScene;
		}

		std::vector<Scene*> GetScenes() {
			return loadedScenes;
		}
	}

}