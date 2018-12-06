#include "Scene.h"

GLfloat floorPlane[] = { -25.f, 0.f, -25.f,
						 -25.f, 0.f, 25.f,
						 25.f, 0.f, 25.f,
						 25.f, 0.f, 25.f };

GLfloat wallPlane[] = { -6, 6, -3.5,
						5, -0.2, -3.5};

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_LIGHTING);								// Enables Lighting
	glEnable(GL_TEXTURE_2D);							// Enables Textures
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Other OpenGL / render setting should be applied here.
	glutWarpPointer(width / 2, height / 2);
	freeCam.Update();

	//Load Textures
	skyboxTex = SOIL_load_OGL_texture
	(
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	floorTex = SOIL_load_OGL_texture
	(
		"gfx/stone_bricks.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	//Load models
	mouse.load("models/Computer Mouse.obj", "models/ComputerMouse.jpg");
	laptop.load("models/Laptop.obj", "gfx/laptopTex.jpg");

	//Initialise procedural shapes
	floor.Init(5, 50, 50);

	// Initialise scene variables
}

void Scene::handleInput(float dt)
{
	float camChanged = false;
	// Handle user input

	// Toggle wireframe mode
	if (input->isKeyDown('p'))
	{
		GLint polygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, &polygonMode[0]);

		if (polygonMode[1] == GL_FILL)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else if (polygonMode[1] == GL_LINE)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		input->SetKeyUp('p');
	}

	#pragma region Camera Control
	//Move forward
	if (input->isKeyDown('w'))
	{
		freeCam.MoveForward(dt, 5);
		camChanged = true;
	}

	//Move left
	if (input->isKeyDown('a'))
	{
		freeCam.MoveLeft(dt, 5);
		camChanged = true;
	}

	//Move backward
	if (input->isKeyDown('s'))
	{
		freeCam.MoveBackward(dt, 5);
		camChanged = true;
	}

	//Move Right
	if (input->isKeyDown('d'))
	{
		freeCam.MoveRight(dt, 5);
		camChanged = true;
	}

	//Move up
	if (input->isKeyDown(32))
	{
		freeCam.MoveUp(dt);
		camChanged = true;
	}

	//Move down
	if (input->isKeyDown('c'))
	{
		freeCam.MoveDown(dt);
		camChanged = true;
	}

	//Camera rotation along the x-axis
	if (input->getMouseX() != width / 2)
	{
		freeCam.RotateYaw((input->getMouseX() - width / 2) * 0.2);
		camChanged = true;
	}

	//Camera rotation along the y-axis
	if (input->getMouseY() != height / 2)
	{
		freeCam.RotatePitch(-(input->getMouseY() - height / 2) * 0.2);
		camChanged = true;
	}


	if (framecount < 2)
	{
		freeCam.SetPitch(0);
		freeCam.SetYaw(0);
		freeCam.SetRoll(0);
		camChanged = true;
		framecount++;
	}

	glutWarpPointer(width / 2, height / 2);
	if (camChanged) freeCam.Update();
#pragma endregion
}

void Scene::update(float dt)
{
	// update scene related variables.
	glowball.Update(dt);

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() 
{

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(freeCam.GetPosX(), freeCam.GetPosY(), freeCam.GetPosZ(),
			freeCam.GetLookAtX(), freeCam.GetLookAtY(), freeCam.GetLookAtZ(),
			freeCam.GetUpX(), freeCam.GetUpY(), freeCam.GetUpZ());

	// Lighting Setup
	#pragma region Sun
	GLfloat Sun_Ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat Sun_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Sun_Position[] = { 0.0f, 20.0f, 10.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, Sun_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Sun_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Sun_Position);
	glEnable(GL_LIGHT0);
#pragma endregion

	#pragma region Light Ball
	glPushMatrix();
		GLfloat Ball_Ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
		GLfloat Ball_Diffuse[] = { 1.0f, 1.0f, 0.4f, 1.0f };
		GLfloat Ball_Position[] = { glowball.position.x, glowball.position.y, glowball.position.z, 1.0f };

		glRotatef(glowball.rotation.y, 0, 1, 0);

		glLightfv(GL_LIGHT1, GL_AMBIENT, Ball_Ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, Ball_Diffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, Ball_Position);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.03);
		
	glPopMatrix();
#pragma endregion

	//Initialise shadow matrix
	float shadowMatrix[16];
	shadow.generateShadowMatrix(shadowMatrix, Sun_Position, floorPlane);

	// Render geometry/scene here -------------------------------------
	RenderSkybox();

	//Floor stencil (stop shadows going past floor)
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);

	floor.Render();

	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	//Floor Generation
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, floorTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		floor.Render();
	glPopMatrix();

	//Render Floor Shadows
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

		glColor3f(0.01f, 0.01f, 0.01f);	//Shadow's colour
		glPushMatrix();
			glMultMatrixf((GLfloat *)shadowMatrix);
			//Translate to floor and draw shadow
			Contents();
		glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	//Disable Shadow Stencil
	glDisable(GL_STENCIL_TEST);

	glEnable(GL_LIGHT1);

	//Render scene contents
	Contents();

	// End render geometry --------------------------------------
	
	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::RenderSkybox()
{
	glBindTexture(GL_TEXTURE_2D, skyboxTex);
	glPushMatrix();
		glTranslatef(freeCam.GetPosX(), freeCam.GetPosY(), freeCam.GetPosZ());
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);

		glBegin(GL_QUADS);
			//Front Face
			glTexCoord2f(0.25f, 0.25f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.5f, 0.25f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(0.25f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);

			//Right Face
			glTexCoord2f(0.5f, 0.25f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.75f, 0.25f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.75f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);

			//Bottom Face
			glTexCoord2f(0.25f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.5f, 0.75f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glTexCoord2f(0.25f, 0.75f);
			glVertex3f(-0.5f, -0.5f, -0.5f);

			//Left Face
			glTexCoord2f(0.25f, 0.25f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.0f, 0.25f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.0f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(0.25f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);

			//Top Face
			glTexCoord2f(0.25f, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.5f, 0.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.5f, 0.25f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glTexCoord2f(0.25f, 0.25f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

			//Back Face
			glTexCoord2f(1.0f, 0.25f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.75f, 0.25f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.75f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();

		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	glPopMatrix();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 1000.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);
	glutWarpPointer(width / 2, height / 2);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	sprintf_s(camLocation, "Camera: %f -x, %f -y, %f -z", freeCam.GetPosX(), freeCam.GetPosY(), freeCam.GetPosZ());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, camLocation);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void Scene::Contents()
{
	glPushMatrix();
		glRotatef(glowball.rotation.y, 0, 1, 0);
		glowball.Render();
	glPopMatrix();

	#pragma region Office Area
	//Office Area
	glPushMatrix();
		glTranslatef(desk.position.x, desk.position.y, desk.position.z);
		//Creates and renders the desk to the screen
		glPushMatrix();
			desk.Render();	//Render the desk object
			//Items on top of desk
			glPushMatrix();
				glTranslatef(0, 1.1, 0);	//Translate to top of desk
				//Placing monitor on desk
				glPushMatrix();
					glScalef(0.15, 0.15, 0.15);
					laptop.render();		//Render the laptop model
				glPopMatrix();

				//Placing mouse on desk
				glPushMatrix();
					glTranslatef(0.55, 0, 0);
					glRotatef(90, 0, 1, 0);
					glScalef(0.15, 0.15, 0.15);

					mouse.render();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		
		glPushMatrix();
			//Set translate relative to desk
			glTranslatef(brickWall.position.x, brickWall.position.y, brickWall.position.z);
			brickWall.Render();
		glPopMatrix();
	glPopMatrix();
#pragma endregion

}
