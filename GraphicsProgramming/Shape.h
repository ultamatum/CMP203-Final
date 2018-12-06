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

		bool isQuads;

		vector<float> vertices;
		vector<float> normals;
		vector<float> texCoords;
};
#endif 
