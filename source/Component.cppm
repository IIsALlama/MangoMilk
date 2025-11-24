export module Component;
#include <typeinfo>

namespace MangoMilk {
	export struct Component 
	{
	private:

	public:
		virtual ~Component() = default;

		void* entity;

		const char* GetName() {
			return typeid(*this).name();
		}

		void Update() {

		}
	};
}
