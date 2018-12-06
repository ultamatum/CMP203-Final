#include "BrickWall.h"

BrickWall::BrickWall()
{
	texture = SOIL_load_OGL_texture
	(
		"gfx/bricks.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	model.Init(2, 2, 0.1, 3);

	position = { 0, 1, -0.8 };
}

BrickWall::~BrickWall() {}

//Renders the wall behind the desk (With hole to allow for window)
//Walls are 2 x 2 unit tiles that are used to make a larger wall
void BrickWall::Render()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	for (int y = 0; y < 3; y++)
	{
		for (int x = -2; x < 3; x++)
		{
			if ((x != 0 && x != -1 && x != 1) || y != 1)
			{
				glPushMatrix();
				glTranslatef(2 * x, 2 * y, 0);
				model.Render();
				glPopMatrix();
			}
		}
	}

	glBindTexture(GL_TEXTURE_2D, NULL);

	//Render window inside wall
	glPushMatrix();
		glColor4f(0, 0, 0.2f, 0.3f);
		glTranslatef(-3, 3, 0);
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);

		glBegin(GL_QUADS);
			glVertex3f(0, 0, 0);

			glVertex3f(0, -2, 0);

			glVertex3f(6, -2, 0);

			glVertex3f(6, 0, 0);
		glEnd();

		glEnable(GL_LIGHTING);
	glPopMatrix();
}
