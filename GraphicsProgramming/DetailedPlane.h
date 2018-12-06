#pragma once
#include "Shape.h"

class DetailedPlane : public Shape 
{
	public:
		DetailedPlane();
		~DetailedPlane();

		void Init(int resPerUnit, float width, float depth);

		int GetRes() { return resolution; };
		float GetWidth() { return width; };
		float GetDepth() { return depth; };

		void SetRes(int res)
		{
			resolution = res;
			Init(res, width, depth);
		};

		void SetWidth(float w)
		{
			width = w;
			Init(resolution, width, depth);
		};

		void SetDepth(int d)
		{
			depth = d;
			Init(resolution, width, depth);
		};

	private:
		int resolution;
		float width;
		float depth;
};

