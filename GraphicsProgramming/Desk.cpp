#include "Desk.h"

Desk::Desk()
{
	texture = SOIL_load_OGL_texture
	(
		"gfx/light_wood.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	position = { 0, 0, -3 };
}

Desk::~Desk(){}

void Desk::Render()
{
	glScalef(1.5, 1.5, 1.5);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	#pragma region Render Desk

	glPushMatrix();
		//Desk Top
		glPushMatrix();
			glTranslatef(0, 1, 0);

			glBegin(GL_QUADS);
				#pragma region Top
				//Bottom Left
				glNormal3f(0, 1, 0);
				glTexCoord2f(0, 1);
				glVertex3f(-1, 0.1, 0.5);

				//Bottom Right
				glNormal3f(0, 1, 0);
				glTexCoord2f(1, 1);
				glVertex3f(1, 0.1, 0.5);

				//Top Right
				glNormal3f(0, 1, 0);
				glTexCoord2f(1, 0);
				glVertex3f(1, 0.1, -0.5);

				//Top Left
				glNormal3f(0, 1, 0);
				glTexCoord2f(0, 0);
				glVertex3f(-1, 0.1, -0.5);
			#pragma endregion

				#pragma region Bottom
				//Bottom Left
				glNormal3f(0, -1, 0);
				glTexCoord2f(0, 1);
				glVertex3f(-1, 0, 0.5);

				//Bottom Right
				glNormal3f(0, -1, 0);
				glTexCoord2f(2, 1);
				glVertex3f(1, 0, 0.5);

				//Top Right
				glNormal3f(0, -1, 0);
				glTexCoord2f(2, 0);
				glVertex3f(1, 0, -0.5);

				//Top Left
				glNormal3f(0, -1, 0);
				glTexCoord2f(0, 0);
				glVertex3f(-1, 0, -0.5);
			#pragma endregion

				#pragma region Left
				//Bottom Left
				glNormal3f(-1, 0, 0);
				glTexCoord2f(0, 0.6);
				glVertex3f(-1, 0, 0.5);

				//Bottom Right
				glNormal3f(-1, 0, 0);
				glTexCoord2f(1, 0.6);
				glVertex3f(-1, 0, -0.5);

				//Top Right
				glNormal3f(-1, 0, 0);
				glTexCoord2f(1, 0.5);
				glVertex3f(-1, 0.1, -0.5);

				//Top Left
				glNormal3f(-1, 0, 0);
				glTexCoord2f(0, 0.5);
				glVertex3f(-1, 0.1, 0.5);
			#pragma endregion

				#pragma region Right
				//Bottom Left
				glNormal3f(1, 0, 0);
				glTexCoord2f(0, 0.1);
				glVertex3f(1, 0, 0.5);

				//Bottom Right
				glNormal3f(1, 0, 0);
				glTexCoord2f(2, 0.1);
				glVertex3f(1, 0, -0.5);

				//Top Right
				glNormal3f(1, 0, 0);
				glTexCoord2f(2, 0.0);
				glVertex3f(1, 0.1, -0.5);

				//Top Left
				glNormal3f(1, 0, 0);
				glTexCoord2f(0, 0.0);
				glVertex3f(1, 0.1, 0.5);
			#pragma endregion
	
				#pragma region Front
				//Bottom Left
				glNormal3f(0, 0, 1);
				glTexCoord2f(0, 0.6);
				glVertex3f(1, 0, 0.5);

				//Bottom Right
				glNormal3f(0, 0, 1);
				glTexCoord2f(2, 0.6);
				glVertex3f(-1, 0, 0.5);

				//Top Right
				glNormal3f(0, 0, 1);
				glTexCoord2f(2, 0.5);
				glVertex3f(-1, 0.1, 0.5);

				//Top Left
				glNormal3f(0, 0, 1);
				glTexCoord2f(0, 0.5);
				glVertex3f(1, 0.1, 0.5);
			#pragma endregion

				#pragma region Back 
				//Bottom Left
				glNormal3f(0, 0, -1);
				glTexCoord2f(0, 0.6);
				glVertex3f(1, 0, -0.5);

				//Bottom Right
				glNormal3f(0, 0, -1);
				glTexCoord2f(2, 0.6);
				glVertex3f(-1, 0, -0.5);

				//Top Right
				glNormal3f(0, 0, -1);
				glTexCoord2f(2, 0.5);
				glVertex3f(-1, 0.1, -0.5);

				//Top Left
				glNormal3f(0, 0, -1);
				glTexCoord2f(0, 0.5);
				glVertex3f(1, 0.1, -0.5);
			#pragma endregion
			glEnd();
		glPopMatrix();

		//Right Leg
		glPushMatrix();
			glTranslatef(1, 0, 0);
			glBegin(GL_QUADS);
				#pragma region Front
				//Bottom Left
				glNormal3f(1, 0, 0);
				glTexCoord2f(0, 1);
				glVertex3f(0, 0, -0.5);

				//Bottom Right
				glNormal3f(1, 0, 0);
				glTexCoord2f(2, 1);
				glVertex3f(0, 0, 0.5);

				//Top Right
				glNormal3f(1, 0, 0);
				glTexCoord2f(2, 0);
				glVertex3f(0, 1, 0.5);

				//Top Left
				glNormal3f(1, 0, 0);
				glTexCoord2f(0, 0);
				glVertex3f(0, 1, -0.5);
			#pragma endregion

				#pragma region Back
				//Bottom Left
				glNormal3f(-1, 0, 0);
				glTexCoord2f(0, 1);
				glVertex3f(-0.1, 0, -0.5);

				//Bottom Right
				glNormal3f(-1, 0, 0);
				glTexCoord2f(2, 1);
				glVertex3f(-0.1, 0, 0.5);

				//Top Right
				glNormal3f(-1, 0, 0);
				glTexCoord2f(2, 0);
				glVertex3f(-0.1, 1, 0.5);

				//Top Left
				glNormal3f(-1, 0, 0);
				glTexCoord2f(0, 0);
				glVertex3f(-0.1, 1, -0.5);
			#pragma endregion

				#pragma region Right
				//Bottom Left
				glNormal3f(0, 0, -1);
				glTexCoord2f(0, 2);
				glVertex3f(0, 0, -0.5);

				//Bottom Right
				glNormal3f(0, 0, -1);
				glTexCoord2f(0.1, 2);
				glVertex3f(-0.1, 0, -0.5);

				//Top Right
				glNormal3f(0, 0, -1);
				glTexCoord2f(0.1, 0);
				glVertex3f(-0.1, 1, -0.5);

				//Top Left
				glNormal3f(0, 0, -1);
				glTexCoord2f(0, 0);
				glVertex3f(0, 1, -0.5);
			#pragma endregion

				#pragma region Left
				//Bottom Left
				glNormal3f(0, 0, 1);
				glTexCoord2f(0, 2);
				glVertex3f(0, 0, 0.5);

				//Bottom Right
				glNormal3f(0, 0, 1);
				glTexCoord2f(0.1, 2);
				glVertex3f(-0.1, 0, 0.5);

				//Top Right
				glNormal3f(0, 0, 1);
				glTexCoord2f(0.1, 0);
				glVertex3f(-0.1, 1, 0.5);

				//Top Left
				glNormal3f(0, 0, 1);
				glTexCoord2f(0, 0);
				glVertex3f(0, 1, 0.5);
			#pragma endregion
			glEnd();
		glPopMatrix();

		//Left Leg
		glPushMatrix();
			glTranslatef(-0.9, 0, 0);
			glBegin(GL_QUADS);
				#pragma region Front
					//Bottom Left
					glNormal3f(1, 0, 0);
					glTexCoord2f(0, 1);
					glVertex3f(0, 0, -0.5);

					//Bottom Right
					glNormal3f(1, 0, 0);
					glTexCoord2f(2, 1);
					glVertex3f(0, 0, 0.5);

					//Top Right
					glNormal3f(1, 0, 0);
					glTexCoord2f(2, 0);
					glVertex3f(0, 1, 0.5);

					//Top Left
					glNormal3f(1, 0, 0);
					glTexCoord2f(0, 0);
					glVertex3f(0, 1, -0.5);
				#pragma endregion

				#pragma region Back
					//Bottom Left
					glNormal3f(-1, 0, 0);
					glTexCoord2f(0, 1);
					glVertex3f(-0.1, 0, -0.5);

					//Bottom Right
					glNormal3f(-1, 0, 0);
					glTexCoord2f(2, 1);
					glVertex3f(-0.1, 0, 0.5);

					//Top Right
					glNormal3f(-1, 0, 0);
					glTexCoord2f(2, 0);
					glVertex3f(-0.1, 1, 0.5);

					//Top Left
					glNormal3f(-1, 0, 0);
					glTexCoord2f(0, 0);
					glVertex3f(-0.1, 1, -0.5);
				#pragma endregion

				#pragma region Right
					//Bottom Left
					glNormal3f(0, 0, -1);
					glTexCoord2f(0, 2);
					glVertex3f(0, 0, -0.5);

					//Bottom Right
					glNormal3f(0, 0, -1);
					glTexCoord2f(0.1, 2);
					glVertex3f(-0.1, 0, -0.5);

					//Top Right
					glNormal3f(0, 0, -1);
					glTexCoord2f(0.1, 0);
					glVertex3f(-0.1, 1, -0.5);

					//Top Left
					glNormal3f(0, 0, -1);
					glTexCoord2f(0, 0);
					glVertex3f(0, 1, -0.5);
				#pragma endregion

				#pragma region Left
					//Bottom Left
					glNormal3f(0, 0, 1);
					glTexCoord2f(0, 2);
					glVertex3f(0, 0, 0.5);

					//Bottom Right
					glNormal3f(0, 0, 1);
					glTexCoord2f(0.1, 2);
					glVertex3f(-0.1, 0, 0.5);

					//Top Right
					glNormal3f(0, 0, 1);
					glTexCoord2f(0.1, 0);
					glVertex3f(-0.1, 1, 0.5);

					//Top Left
					glNormal3f(0, 0, 1);
					glTexCoord2f(0, 0);
					glVertex3f(0, 1, 0.5);
				#pragma endregion
			glEnd();
		glPopMatrix();
	glPopMatrix();
#pragma endregion

	glBindTexture(GL_TEXTURE_2D, NULL);
}