#include "maths.h"

namespace MangoMilk {
	Vector2::Vector2(float _x, float _y) 
		: x(_x), y(_y)
	{}

	Vector2::Vector2(void) {
		x = 0.0f;
		y = 0.0f;
	}

}
