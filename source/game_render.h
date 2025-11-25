#pragma once

#include "common.h"

namespace MangoMilk {
	namespace GameRender {
		extern unsigned int outputTexture;

		void Initialize();
		void Terminate();
		bool IsInitialized();
		void Rescale(float width, float height);
		void Render();
	}
}
