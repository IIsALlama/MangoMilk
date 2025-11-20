#pragma once

#include "game_manager.h"
#include "entity.h"
#include "transform.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <vector>

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
