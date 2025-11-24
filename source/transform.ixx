export module Transform;

import Component;

namespace MangoMilk {
	export class Vector2
	{
	private:

	public:
		float x;
		float y;

		Vector2(float _x, float _y) {
			x = _x;
			y = _y;
		}

		Vector2() {
			x = 0.0f;
			y = 0.0f;
		}
	};

	export class Transform : public Component
	{
	private:

	public:
		Vector2 position = Vector2(0.0f, 0.0f);
		Vector2 scale = Vector2(1.0f, 1.0f);
		float rotation = 0.0f;

		void Update() {

		};
	};

}