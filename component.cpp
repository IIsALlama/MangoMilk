#include "component.h"

namespace MangoMilk {
	const char* Component::GetName() {
		return typeid(*this).name();
	}

	void Component::Update() {

	}

}