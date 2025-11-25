#pragma once

#include "common.h"
#include "game_render.h"

import Entity;

namespace MangoMilk {
	class Entity;
	namespace GameManager {

		void GameLoop();

		Entity* Instantiate(Entity* e);

		std::vector<Entity*> GetEntities();

		template <typename T> Entity* FindEntityOfType();
		Entity* FindEntityWithName(const char* name);
		Entity* GetEntity(int id);
	}
}