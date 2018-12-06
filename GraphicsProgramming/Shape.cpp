#include "shape.h"

void Shape::Render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	glNormalPointer(GL_FLOAT, 0, &normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

	if (isQuads)
	{
		glDrawArrays(GL_QUADS, 0, vertices.size() / 3);
	} else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//Default update method just to move object by it's current velocity (will only be used if collisions get implemented in time)
void Shape::Update()
{
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;
}