#pragma once
#include <typeinfo>
#include <Refureku/Refureku.h>
#include <Runtime/ReflectionModule.h>
#include <Runtime/Meta.h>

namespace MangoMilk {
	class Entity;

	struct Component
	{
	private:

	public:
		virtual ~Component() = default;

		Entity* entity;

		Meta(Range(0.0f, 100.0f))
		float testValue = 10.0f;

		int testValue2 = 10;

		const char* GetName();
		virtual void Update();
	} Meta(Enable);

	struct Test
	{
		int testValue2 = 10;

		Test(void) = default;
	} Meta(Enable);
}