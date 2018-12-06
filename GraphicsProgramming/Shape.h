#ifndef _SHAPE_H
#define _SHAPE_H

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <vector>
#include "Vector3.h"

using std::vector;

class Shape
{
	public:
		void Render();
		void Update();

		bool isQuads;

		vector<float> vertices;
		vector<float> normals;
		vector<float> texCoords;

		//Position
		Vector3 position = { 0, 0, 0 };

		//Velocity
		Vector3 velocity = { 0, 0, 0 };
};
#endif 
