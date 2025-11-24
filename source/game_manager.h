#pragma once

#include "game_render.h"
#include <vector>
using std::vector;

import Entity;


namespace MangoMilk {
	class Entity;
	namespace GameManager {

		void GameLoop();

		Entity* Instantiate(Entity* e);

		vector<Entity*> GetEntities();

		template <typename T> Entity* FindEntityOfType();
		Entity* FindEntityWithName(const char* name);
		Entity* GetEntity(int id);
	}
}