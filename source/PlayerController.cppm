#include "debugging.h"

export module PlayerController;
import Component;
import Entity;
using namespace MangoMilk;


export class PlayerController : public Component
{
private:

public:
	void Update() {
		Debug::Log("Wahooo!");

		CastOwnerPtr<Entity>()->transform->position.x += 0.1f;
	};
};