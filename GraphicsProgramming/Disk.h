#pragma once
#include "Shape.h"

class Disk : public Shape
{
	public:
		Disk();
		~Disk();

		void Init(int resolution, float radius);
};

