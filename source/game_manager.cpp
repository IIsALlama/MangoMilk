#include "game_manager.h"
#include "game_render.h"
#include <chrono>

import Entity;

namespace MangoMilk {
	namespace GameManager {
		bool gameRunning = false;
		float deltaTime = .0f;
		std::chrono::system_clock::time_point lastFrameTime;
		
		std::vector<Entity*> entities;
		std::vector<Entity*> copiedEntities;

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

		float DeltaTime() {
			return deltaTime;
		}

		void CopyGameState() {
			copiedEntities.clear();
			for (size_t i = 0; i < entities.size(); i++)
			{
				Entity* e = new Entity("");
				*e = *entities[i];
				copiedEntities.push_back(e);
			}
		}

		void GameLoop() {
			auto now = std::chrono::system_clock::now();
			auto ms = std::chrono::duration_cast<std::chrono::microseconds>(now - lastFrameTime).count();
			deltaTime = ms / 1000.0f;
			lastFrameTime = now;

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
			CopyGameState();
		}

		void PauseGame() {

		}

		void QuitGame() {
			gameRunning = false;
			entities = copiedEntities;
		}
	}
}