#pragma once

#include "common.h"

namespace MangoMilk {
	class Entity;
	namespace GameManager {

		void GameLoop();

		Entity* Instantiate(Entity* e);

		std::vector<Entity*> GetEntities();
		void SetEntities(std::vector<Entity*> es);

		template <typename T> Entity* FindEntityOfType();
		Entity* FindEntityWithName(const char* name);
		Entity* GetEntity(int id);
	}
}