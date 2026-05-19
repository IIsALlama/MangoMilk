#include "game_manager.h"

#include "game_render.h"

import Entity;

namespace MangoMilk {
	namespace GameManager {
		bool gameRunning = false;
		
		std::vector<Entity*> entities;

		Entity* Instantiate(Entity* e) {
			entities.push_back(e);
			return e;
		}

		std::vector<Entity*> GetEntities() {
			return entities;
		}

		void SetEntities(std::vector<Entity*> es) {
			entities = es;
		}

		void GameLoop() {
			GameRender::Render();

			if (gameRunning) {
				for (size_t i = 0; i < entities.size(); i++)
				{
					entities[i]->UpdateComponents();
				}
			}
		}

		bool IsGameRunning() {
			return gameRunning;
		}

		void StartGame() {
			gameRunning = true;
		}

		void PauseGame() {

		}

		void QuitGame() {
			gameRunning = false;
		}
	}
}