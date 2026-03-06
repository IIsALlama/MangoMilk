#pragma once

#include "common.h"

namespace MangoMilk {
	namespace GameRender {
		extern unsigned int outputTexture;
		extern GLsizei W;
		extern GLsizei H;
		extern float aspect;

		void Initialize();
		void Terminate();
		bool IsInitialized();
		void Rescale(float width, float height);
		void Render();
	}
}
