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

	//Camera setups
	cameras[FPSCAM].Init(2, Vector3(0, 2.5, 0), Vector3(25, 0, 25), true, false, true);
	cameras[FREECAM].Init(5, Vector3(10, 10, 10), Vector3(1000, 0, 1000), true, true, true);
	cameras[ORBITALCAM].InitOrbital(Vector3(0, 2, 0), 20, 6, 0.1);
	cameras[STATICCAM].InitStatic(Vector3(0.8, 2.5, -2));

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

	if (input->isLeftMouseButtonPressed())
	{
		PickRects();

		input->setLeftMouseButton(false);
	}

	//Switch camera
	if (input->isKeyDown('1')) curCam = FPSCAM;

	if (input->isKeyDown('2')) curCam = FREECAM;

	if (input->isKeyDown('3')) curCam = ORBITALCAM;

	if (input->isKeyDown('4')) curCam = STATICCAM;

	if(curCam != ORBITALCAM) cameras[curCam].HandleInput(input, dt, width, height);

	glutWarpPointer(width / 2, height / 2);
}

void Scene::update(float dt)
{
	// update scene related variables.
	glowball.Update(dt);

	if (red < 255 && green == 0)
	{
		red++;
		blue--;
	}
	else if (green < 255 && blue == 0)
	{
		green++;
		red--;
	}
	else if (blue < 255)
	{
		blue++;
		green--;
	}

	if (curCam == ORBITALCAM) 
		cameras[curCam].Update(dt);

	//cameras[ORBITALCAM].Update(dt);

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
	gluLookAt(cameras[curCam].GetPosX(), cameras[curCam].GetPosY(), cameras[curCam].GetPosZ(),
			cameras[curCam].GetLookAtX(), cameras[curCam].GetLookAtY(), cameras[curCam].GetLookAtZ(),
			cameras[curCam].GetUpX(), cameras[curCam].GetUpY(), cameras[curCam].GetUpZ());

	// Lighting Setup
	#pragma region Sun
	GLfloat Sun_Ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat Sun_Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Sun_Position[] = { 0.0f, 20.0f, 10.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, Sun_Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Sun_Diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, Sun_Position);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
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
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.25);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.15);

		glEnable(GL_LIGHT1);
	glPopMatrix();
#pragma endregion

	#pragma region RGB Light
	glPushMatrix();
		GLfloat RGB_Ambient[] = { 0.2, 0.2, 0.2, 1 };
		GLfloat RGB_Diffuse[] = { red / 255, blue / 255, green / 255, 1 };
		GLfloat RGB_Position[] = { 0.81f, 3, -3, 1.0f };
		GLfloat RGB_Spot_Direction[] = { 0.0, -1.0f, 0.0f };

		glLightfv(GL_LIGHT2, GL_AMBIENT, RGB_Ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, RGB_Diffuse);
		glLightfv(GL_LIGHT2, GL_POSITION, RGB_Position);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 60.0f);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, RGB_Spot_Direction);
		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.4);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.3);
		
		if(RGBon) glEnable(GL_LIGHT2);
		else glDisable(GL_LIGHT2);
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

	//Render scene contents
	Contents();

	// End render geometry --------------------------------------
	
	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

//Function to create and render a skybox around the camera
void Scene::RenderSkybox()
{
	glBindTexture(GL_TEXTURE_2D, skyboxTex);
	glPushMatrix();
		glTranslatef(cameras[curCam].GetPosX(), cameras[curCam].GetPosY(), cameras[curCam].GetPosZ());
		glDisable(GL_DEPTH_TEST);	//Need to disable depth test so skybox appears behind the scene
		glDisable(GL_LIGHTING);		//Disable lighting so skybox isn't affected

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
	glDisable(GL_LIGHTING);
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	sprintf_s(camLocation, "Camera: %f -x, %f -y, %f -z", cameras[curCam].GetPosX(), cameras[curCam].GetPosY(), cameras[curCam].GetPosZ());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
	displayText(-1.f, 0.84f, 1.f, 0.f, 0.f, camLocation);
	glEnable(GL_LIGHTING);
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

void Scene::PickRects()
{
	GLuint selectBuf[BUFSIZ];
	GLint hits;
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);	//Gets the viewport region and stores it in the variable
	glSelectBuffer(BUFSIZ, selectBuf);		//Sets the select buffer
	glRenderMode(GL_SELECT);				//Sets the render mode to selection mode

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		//Creates a selection matrix centred around the mouse
		gluPickMatrix((GLdouble)input->getMouseX(), (GLdouble)(viewport[3] - input->getMouseY()), 5.0, 5.0, viewport);
		gluPerspective(fov, (viewport[3] / viewport[4]) , nearPlane, farPlane);		//Sets the correct perspective

		RenderSkybox();
		Contents();
	glPopMatrix();
	hits = glRenderMode(GL_RENDER);
	ProcessHits(hits, selectBuf);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}

void Scene::ProcessHits(GLint hits, GLuint selectBuf[])
{
	unsigned int i, j;
	GLuint names, *ptr;
	float z1, z2;

	printf("hits = %d\n", hits);
	ptr = (GLuint *)selectBuf;

	for (i = 0; i < hits; i++) { /* for each hit */
		names = *ptr; ptr++;
		z1 = (float)*ptr / 0xffffffff; ptr++; /* scale 0-1 */
		z2 = (float)*ptr / 0xffffffff; ptr++;

		for (j = 0; j < names; j++) { /* for each name */
			if (*ptr == 1)
			{
				if (RGBon) RGBon = false;
				else RGBon = true;
			}
			ptr++;
		}
	}

}

//Function to store the contents of the scene
void Scene::Contents()
{
	glInitNames();
	glPushName(-1);

	glPushMatrix();
		glRotatef(glowball.rotation.y, 0, 1, 0);
		glLoadName(16);
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

					glLoadName(1);
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
