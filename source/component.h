#pragma once
#include <typeinfo>

#include <meta/factory.hpp>

namespace MangoMilk {
	class Entity;

	struct Component
	{
	private:

	public:
		virtual ~Component() = default;

		Entity* entity;

		const char* GetName();
		virtual void Update();
	};
}