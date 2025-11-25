#include "game_manager.h"

#include "game_render.h"

import Entity;

namespace MangoMilk {
	namespace GameManager {
		std::vector<Entity*> entities;

		Entity* Instantiate(Entity* e) {
			entities.push_back(e);
			return e;
		}

		std::vector<Entity*> GetEntities() {
			return entities;
		}

		void GameLoop() {
			GameRender::Render();
		}
	}
}