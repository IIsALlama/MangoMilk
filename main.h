#pragma once

#include <string>
#include <fstream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <assert.h>

#include "debugging.h"
#include "entity.h"
#include "game_render.h"
#include "game_manager.h"
#include "component.h"
#include "transform.h"

using namespace MangoMilk;