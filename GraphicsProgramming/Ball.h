#pragma once
#include "GameObject.h"
#include "Sphere.h"

class Ball : public GameObject
{
	public:
		Ball();
		~Ball();

		void Render();
		void Update(float dt);

	private:
		Sphere model;
};

