export module Entity;

#include <vector>
using std::vector;

#include <iostream>

import Component;
import Transform;

namespace MangoMilk {

	export class Entity
	{
	private:
		vector<Component*> components;

	public:
		std::string name;
		Transform* transform;

		Entity(std::string _name) {
			Transform* t = new Transform();
			AddComponent(t);
			transform = t;

			name = _name;
		}

		void AddComponent(Component* c) {
			c->ownerPtr = this;
			components.push_back(c);
		}

		void RemoveComponent(Component* c) {
			int index = -1;
			for (size_t i = 0; i < components.size(); i++)
			{
				if (components[i] == c) {
					index = i;
				}
			}

			if (index == -1) {
				return;
			}

			components.erase(components.begin() + index);
			delete c;
		}

		template <typename T> T* GetComponent() {
			for (size_t i = 0; i < components.size(); i++)
			{
				T* casted = dynamic_cast<T*>(components[i]);
				if (casted) {
					return casted;
				}
			}

			return nullptr;
		}

		vector<Component*> GetAllComponents() {
			return components;
		}

		void UpdateComponents() {
			for (size_t i = 0; i < components.size(); i++)
			{
				components[i]->Update();
			}
		}
	};
}