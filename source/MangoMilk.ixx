export module MangoMilk;

namespace MangoMilk {
	export struct Test
	{
	private:

	public:
		virtual ~Test() = default;

		int testInt = 10;
		float testFloat = 5.0f;

		Test(int a, float b) {
			testInt = a;
			testFloat = b;
		}
	};
}