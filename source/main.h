#pragma once

#include <string>
#include <fstream>
#include <thread>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <cassert>
#include <meta/factory.hpp>
#include <meta/meta.hpp>

#include "debugging.h"
#include "Game.h"
#include "ECS.h"

using namespace MangoMilk;