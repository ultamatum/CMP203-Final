#include "Ball.h"

Ball::Ball() 
{
	texture = SOIL_load_OGL_texture
	(
		"gfx/glowstone.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	model.Init(20, 20, 1);
	
	position.y = 3;
	position.z = 10;
}

Ball::~Ball() {}

void Ball::Update(float dt)
{
	rotation.y += 10 * dt;
}

void Ball::Render()
{
	glTranslatef(position.x, position.y, position.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	model.Render();
	glBindTexture(GL_TEXTURE_2D, NULL);
}
