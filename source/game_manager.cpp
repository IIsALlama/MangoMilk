#include "game_manager.h"

namespace MangoMilk {
	namespace GameManager {
		vector<Entity*> entities;

		Entity* Instantiate(Entity* e) {
			entities.push_back(e);
			return e;
		}

		vector<Entity*> GetEntities() {
			return entities;
		}

		void GameLoop() {
			GameRender::Render();
		}
	}
}