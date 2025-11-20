#include "game_manager.h"

namespace MangoMilk {
	namespace GameManager {
		vector<Entity*> entities;

		void AddEntity(Entity* e) {
			entities.push_back(e);
		}

		vector<Entity*> GetEntities() {
			return entities;
		}

		void GameLoop() {
			GameRender::Render();
		}
	}
}