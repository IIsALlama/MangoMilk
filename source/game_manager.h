#pragma once

#include <vector>
using std::vector;

#include "entity.h"

namespace MangoMilk {
	class Entity;
	namespace GameManager {

		void GameLoop();

		void AddEntity(Entity* e);
		vector<Entity*> GetEntities();
		template <typename T> Entity* FindEntityOfType();
		Entity* FindEntityWithName(const char* name);
		Entity* GetEntity(int id);
	}
}