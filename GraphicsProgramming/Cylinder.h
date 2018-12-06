#pragma once
#include "Shape.h"

class Cylinder : public Shape
{
	public:
		Cylinder();
		~Cylinder();

		void Init(int lat, int lon, float h, float r);

		int GetLat() { return latitude; };
		int GetLong() { return longitude; };
		float GetHeight() { return height; };
		float GetRadius() { return radius; };

		void SetLat(int value)
		{
			latitude = value;
			Init(latitude, longitude, height, radius);
		};

		void SetLong(int value)
		{
			longitude = value;
			Init(latitude, longitude, height, radius);
		};

		void SetHeight(float value)
		{
			height = value;
			Init(latitude, longitude, height, radius);
		};

		void SetRadius(float value)
		{
			radius = value;
			Init(latitude, longitude, height, radius);
		};

	private:
		int longitude;
		int latitude;
		float height;
		float radius;
};

