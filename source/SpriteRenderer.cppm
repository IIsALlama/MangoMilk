export module SpriteRenderer;

import Component;

namespace MangoMilk {

	export class Colour
	{
	public:
		float r;
		float g;
		float b;

		Colour(float _r, float _g, float _b){
			r = _r;
			g = _g;
			b = _b;
		}

		Colour() {
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
		}
	};

	export class SpriteRenderer : public Component
	{
	private:

	public:
		Colour colour;

		SpriteRenderer() { }

		void Update() {

		};
	};
}