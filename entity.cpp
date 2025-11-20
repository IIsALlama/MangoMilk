#include "entity.h"

namespace MangoMilk {
	Entity::Entity(const char* _name) {
		GameManager::AddEntity(this);

		Transform* t = new Transform();
		AddComponent(t);
		transform = t;

		name = _name;
	}

	void Entity::AddComponent(Component* component) {
		component->entity = this;
		components.push_back(component);
	}

	void Entity::RemoveComponent(Component* component) {
		int index = -1;
		for (size_t i = 0; i < components.size(); i++)
		{
			if (components[i] == component) {
				index = i;
			}
		}

		if (index == -1) {
			std::cout << "Component not found";
			return;
		}

		components.erase(components.begin() + index);
		delete component;
	}
	
	template <typename T> Component* Entity::GetComponent() {
		for (size_t i = 0; i < components.size(); i++)
		{
			if (typeid(components[i]) == T) {
				return components[i];
			}
		}

		return NULL;
	}

	vector<Component*> Entity::GetAllComponents() {
		return components;
	}

	void Entity::UpdateComponents() {
		for (size_t i = 0; i < components.size(); i++)
		{
			components[i]->Update();
		}
	}

}