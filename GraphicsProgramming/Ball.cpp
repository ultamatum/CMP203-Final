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

	model.Init(20, 20, 5);
}

Ball::~Ball() {}

void Ball::Render()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	model.Render();
}
