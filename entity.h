#pragma once

#include <iostream>
#include <vector>
#include <typeinfo>

//#include "MangoMilk.h"
#include "component.h"
#include "component_transform.h"
#include "game_manager.h"

using std::vector;

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