export module Transform;

import Component;

namespace MangoMilk {
	export template <typename T>
	struct LinkedListNode
	{
		T data = nullptr;
		struct LinkedListNode* next = nullptr;

		LinkedListNode(T _data) : data(_data) {};
	};

	export template <typename T>
	class LinkedList
	{
		LinkedListNode<T>* start = nullptr;
		LinkedListNode<T>* end = nullptr;

	public:
		int size = 0;

		T operator [](int i) {
			LinkedListNode<T>* current = start;
			for (size_t n = 0; n < i; n++)
			{
				if (current == nullptr || current->next == nullptr) {
					//std::cout << "index out of range of linked list.";
				}
				current = current->next;
			}
			return current->data;
		}

		void push_back(T item) {
			LinkedListNode<T>* newNode = new LinkedListNode<T>(item);
			if (start == nullptr) { start = newNode; end = newNode; }

			end->next = newNode;
			end = end->next;
			size++;
		}

		void push_front(T item) {
			LinkedListNode<T>* newNode = new LinkedListNode<T>(item);
			if (start == nullptr) { start = newNode; end = newNode; }

			LinkedListNode<T>* temp = start;
			start = newNode;
			newNode->next = temp;
			size++;
		}

		void erase(int i) {
			LinkedListNode<T>* last = nullptr;
			LinkedListNode<T>* current = start;
			for (size_t n = 0; n < i; n++)
			{
				if (current->next = nullptr) {
					//std::cout << "index out of range of linked list.";
					return;
				}
				last = current;
				current = current->next;
			}
			last->next = current->next;
			delete current;
			size--;
		}

		int index_of(T item) {
			LinkedListNode<T>* current = start;
			for (size_t n = 0; n < size; n++)
			{
				if (current->data == item) {
					return n;
				}
				current = current->next;
			}
			return -1;
		}

	};

	export class Vector2
	{
	private:

	public:
		float x;
		float y;

		Vector2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		Vector2() {
			x = 0.0f;
			y = 0.0f;
		}

		Vector2 operator+(const Vector2& vec) {
			return Vector2(x + vec.x, y + vec.y);
		}
	};

	export class Transform : public Component
	{
	private:
		LinkedList<Transform*> children;
		Transform* parent = nullptr;
	public:
		Vector2 position = Vector2(0.0f, 0.0f);
		Vector2 scale = Vector2(1.0f, 1.0f);
		float rotation = 0.0f;

		Transform* GetParent() {
			return parent;
		}

		Vector2 GetWorldPosition() {
			if (parent == nullptr) return position;
			Vector2 parentPos = parent->GetWorldPosition();
			return parentPos + position;
		}

		void AddChild(Transform* e) {
			children.push_back(e);
			if (e->parent != nullptr) e->parent->RemoveChild(e);
			e->parent = this;
		}

		void RemoveChild(Transform* e) {
			int index = children.index_of(e);

			if (index != -1) {
				children.erase(index);
				e->parent = nullptr;
			}
		}

		LinkedList<Transform*> GetChildren() {
			return children;
		}

		void Update() {

		};
	};
}