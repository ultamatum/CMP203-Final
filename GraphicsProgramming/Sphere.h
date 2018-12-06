#pragma once

#include "Shape.h"

class Sphere : public Shape
{
	public:
		Sphere();
		~Sphere();

		void Init(int lat, int lon, float r);

		int GetLat() { return latitude; };
		int GetLong() { return longitude; };
		float GetRadius() { return radius; };

		void SetLat(int value) {
			latitude = value;
			Init(latitude, longitude, radius);
		};

		void SetLong(int value) {
			longitude = value;
			Init(latitude, longitude, radius);
		};

		void SetRadius(float value) {
			radius = value;
			Init(latitude, longitude, radius);
		};

	private:
		int latitude;
		int longitude;
		float radius;
};

