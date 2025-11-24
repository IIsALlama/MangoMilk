#pragma once

#include <vector>
using std::vector;
#include <iostream>

#include "Game.h"
#include "entity.h"

import Component;
import Transform;

namespace MangoMilk {

	class Entity
	{
	private:
		vector<Component*> components;

	public:
		const char* name;
		Transform* transform;

		Entity(const char* _name);

		void AddComponent(Component* component);
		void RemoveComponent(Component* component);
		template <typename T> Component* GetComponent();
		vector<Component*> GetAllComponents();
		void UpdateComponents();
	};
}