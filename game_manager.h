#pragma once
#include <iostream>
#include <vector>
using std::vector;

namespace MangoMilk {
	class Entity;
	namespace GameManager {

		void AddEntity(Entity* e);

		vector<Entity*> GetEntities();
		template <typename T> Entity* FindEntityOfType();
		Entity* FindEntityWithName(const char* name);
		Entity* GetEntity(int id);
	}
}