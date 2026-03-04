#include <typeinfo>

export module Component;

namespace MangoMilk {
	
	export struct Component
	{
	private:

	public:
		virtual ~Component() = default;

		void* ownerPtr;

		const char* GetName() {
			return typeid(*this).name();
		}

		template <typename T> T* CastOwnerPtr() {
			return static_cast<T*>(ownerPtr);
		}

		void Update() {

		}
	};
}
