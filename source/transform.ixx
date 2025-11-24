export module Transform;

import Component;
#include "maths.h"

namespace MangoMilk {
	export class Transform : Component
	{
	private:

	public:
		Vector2 position = Vector2(0.0f, 0.0f);
		Vector2 scale = Vector2(1.0f, 1.0f);
		float rotation = 0.0f;

		void Update();
	};
}