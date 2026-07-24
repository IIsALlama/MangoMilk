#include "mangomilk.h"
export module PlayerController;

export class PlayerController : public MangoMilkComponent
{
private:

public:
	void Update() {
		GetEntity()->transform->position.x += 0.001f * GameManager::DeltaTime();
	};
};