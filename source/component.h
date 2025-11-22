#pragma once
#include <typeinfo>

namespace MangoMilk {
	class Entity;

	class Component
	{
	private:

	public:
		virtual ~Component() = default;

		Entity* entity;

		const char* GetName();
		virtual void Update();
	};
}