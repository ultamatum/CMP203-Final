#pragma once
#include "Shape.h"

class Cuboid : public Shape
{
	public:
		Cuboid();
		~Cuboid();

		void Init(float length, float height, float depth, float texScale);

		float GetLength() { return length; };
		float GetHeight() { return height; };
		float GetDepth() { return depth; };
		float GetTexScale() { return texScale; };

		void SetLength(float value)
		{
			length = value;
			Init(length, height, depth, texScale);
		};

		void SetHeight(float value)
		{
			height = value;
			Init(length, height, depth, texScale);
		};

		void SetDepth(float value)
		{
			depth = value;
			Init(length, height, depth, texScale);
		};

		void SetTexScale(float value)
		{
			texScale = value;
			Init(length, height, depth, texScale);
		};

	private:
		float length;
		float height;
		float depth;
		float texScale;
};

