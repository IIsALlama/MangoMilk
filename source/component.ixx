export module Component;

#include <typeinfo>


namespace MangoMilk {
	export struct Component
	{
	private:

	public:
		virtual ~Component() = default;

		//Entity* entity;

		const char* GetName() {
			return typeid(*this).name();
		}

		void Update() {

		}
	};
}