#pragma once

import Component;
import Entity;
using namespace MangoMilk;

#include "debugging.h"
#include "game_manager.h"
#include <iostream>
#
#include <imgui.h>

class MangoMilkComponent : public Component
{
private:

public:
	Entity* GetEntity() {
		return CastOwnerPtr<Entity>();
	}
};