#pragma once

#include <vector>
using std::vector;
#include <iostream>

#include "game_manager.h"
#include "component.h"
#include "transform.h"
#include "maths.h"

namespace MangoMilk {
	class Transform;
	class Component;

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