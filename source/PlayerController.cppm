#include "mangomilk.h"
export module PlayerController;

export class PlayerController : public MangoMilkComponent
{
private:

public:
	float speed = 1.0f;

	void Update() {
		GetEntity()->transform->position.x += (speed / 1000.0f) * GameManager::DeltaTime();
	};
};

