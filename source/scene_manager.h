#pragma once

#include <vector>
#include <iostream>

import Entity;

namespace MangoMilk {
	class Scene
	{
	private:

	public:
		std::string sceneName = "New Scene";
		std::vector<Entity*> entities;
	};

	namespace SceneManager {
		void Initialize();
		void OpenScene(int sceneIndex);
		void SaveCurrentScene();
		Scene* NewScene();
		std::vector<Scene*> GetScenes();
	}

}