#pragma once

#include "MangoMilk.h"

namespace MangoMilk {
	namespace GameRender {
		extern unsigned int outputTexture;

		void Initialize();
		void Terminate();
		void Rescale(float width, float height);
		void Render();
	}
}
