#pragma once

#include "Game.h"
#include "entity.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

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
