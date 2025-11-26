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
		vector<Entity*> children;

	public:
		const char* name;
		Entity* parent = nullptr;
		Transform* transform;

		Entity(const char* _name) {
			Transform* t = new Transform();
			AddComponent(t);
			transform = t;

			name = _name;
		}

		void AddChild(Entity* e) {
			children.push_back(e);
			if (e->parent != nullptr) e->parent->RemoveChild(e);
			e->parent = this;
		}

		void RemoveChild(Entity* e) {
			auto index = std::find(children.begin(), children.end(), e);

			if (index != children.end()) {
				children.erase(index);
				e->parent = nullptr;
			}
		}

		vector<Entity*> GetChildren() {
			return children;
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