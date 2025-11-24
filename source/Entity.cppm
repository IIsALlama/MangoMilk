export module Entity;

#include <vector>
using std::vector;

import Component;
import Transform;

namespace MangoMilk {

	export class Entity
	{
	private:
		vector<Component*> components;

	public:
		const char* name;
		Transform* transform;

		Entity(const char* _name) {
			Transform* t = new Transform();
			AddComponent(t);
			transform = t;

			name = _name;
		}

		void AddComponent(Component* component) {
			component->entity = this;
			components.push_back(component);
		}

		void RemoveComponent(Component* component) {
			int index = -1;
			for (size_t i = 0; i < components.size(); i++)
			{
				if (components[i] == component) {
					index = i;
				}
			}

			if (index == -1) {
				return;
			}

			components.erase(components.begin() + index);
			delete component;
		}

		template <typename T> Component* GetComponent() {
			for (size_t i = 0; i < components.size(); i++)
			{
				if (std::is_same<decltype(*components[i]), T>::value) {
					return components[i];
				}
			}

			return NULL;
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