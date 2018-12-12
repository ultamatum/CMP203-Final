#include "Camera.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::Init(float speed, Vector3 startPos, Vector3 limits, bool xMove, bool yMove, bool zMove)
{
	this->speed = speed;

	this->xMove = xMove;
	this->yMove = yMove;
	this->zMove = zMove;

	pos = startPos;
	posLims = limits;
}

void Camera::InitOrbital(Vector3 target, float radius, float height, float speed)
{
	orbitTarget = target;
	orbitRadius = radius;
	orbitHeight = height;
	this->speed = speed;

	orbital = true;
	up = Vector3(0, 1, 0);
	lookAt = target;
}

void Camera::InitStatic(Vector3 position)
{
	pos = position;

	xMove = false;
	yMove = false;
	zMove = false;
}

void Camera::HandleInput(Input *input, float dt, int width, int height)
{
	float camChanged = false;
	
	if (!orbital)
	{
		#pragma region Camera Control
		//Move forward
		if (input->isKeyDown('w'))
		{
			MoveForward(dt);
			camChanged = true;
		}

		//Move left
		if (input->isKeyDown('a'))
		{
			MoveLeft(dt);
			camChanged = true;
		}

		//Move backward
		if (input->isKeyDown('s'))
		{
			MoveBackward(dt);
			camChanged = true;
		}

		//Move Right
		if (input->isKeyDown('d'))
		{
			MoveRight(dt);
			camChanged = true;
		}

		//Move up
		if (input->isKeyDown(32))
		{
			MoveUp(dt);
			camChanged = true;
		}

		//Move down
		if (input->isKeyDown('c'))
		{
			MoveDown(dt);
			camChanged = true;
		}

		//Camera rotation along the x-axis
		if (input->getMouseX() != width / 2)
		{
			RotateYaw((input->getMouseX() - width / 2) * 0.2);
			camChanged = true;
		}

		//Camera rotation along the y-axis
		if (input->getMouseY() != height / 2)
		{
			RotatePitch(-(input->getMouseY() - height / 2) * 0.2);
			camChanged = true;
		}

		//Oddity with input class that mouse info doesnt update first frame
		if (startDelay < 2)
		{
			SetPitch(0);
			SetYaw(0);
			SetRoll(0);
			camChanged = true;
			startDelay++;
		}

		if (camChanged) Update(dt);
#pragma endregion
	}
}

void Camera::Update(float dt)
{
	if (!orbital)
	{
		float cosR, cosP, cosY;			//Temp cos values for Roll, Pitch, Yaw
		float sinR, sinP, sinY;			//Temp sin values for Roll, Pitch, Yaw

		cosR = cosf(roll * 3.1415 / 180);
		cosP = cosf(pitch * 3.1415 / 180);
		cosY = cosf(yaw * 3.1415 / 180);
		sinR = sinf(roll * 3.1415 / 180);
		sinP = sinf(pitch * 3.1415 / 180);
		sinY = sinf(yaw * 3.1415 / 180);

		//Calculating the forward vector for gluLookat
		forward.x = sinY * cosP;
		forward.y = sinP;
		forward.z = cosP * -cosY;

		//Lookat point
		lookAt.x = pos.x + forward.x;
		lookAt.y = pos.y + forward.y;
		lookAt.z = pos.z + forward.z;

		//Up vector
		up.x = -cosY * sinR - sinY * sinP * cosR;
		up.y = cosP * cosR;
		up.z = -sinY * sinR - sinP * cosR * -cosY;

		//Right vector
		right = forward.cross(up);
	}
	else 
	{
		orbitTheta += speed * dt;

		pos.x = orbitTarget.x + orbitRadius * cos(orbitTheta);
		pos.y = orbitHeight;
		pos.z = orbitTarget.z + orbitRadius * sin(orbitTheta);
	}
}

void Camera::MoveForward(float dt)
{
	if(xMove) pos.x += (forward.x * speed) * dt;
	if(yMove) pos.y += (forward.y * speed) * dt;
	if(zMove) pos.z += (forward.z * speed) * dt;

	if (pos.x > posLims.x) pos.x = posLims.x;
	else if (pos.x < -posLims.x) pos.x = -posLims.x;

	if (pos.z > posLims.z) pos.z = posLims.z;
	else if (pos.z < -posLims.z) pos.z = -posLims.z;
}

void Camera::MoveBackward(float dt)
{
	if (xMove) pos.x -= (forward.x * speed) * dt;
	if (yMove) pos.y -= (forward.y * speed) * dt;
	if (zMove) pos.z -= (forward.z * speed) * dt;

	if (pos.x > posLims.x) pos.x = posLims.x;
	else if (pos.x < -posLims.x) pos.x = -posLims.x;

	if (pos.z > posLims.z) pos.z = posLims.z;
	else if (pos.z < -posLims.z) pos.z = -posLims.z;
}

void Camera::MoveUp(float dt)
{
	if (yMove) pos.y += up.y * dt;
}

void Camera::MoveDown(float dt)
{
	if (yMove) pos.y -= up.y * dt;
}

void Camera::MoveLeft(float dt)
{
	if (xMove) pos.x -= right.x * speed * dt;
	if (zMove) pos.z -= right.z * speed * dt;

	if (pos.x > posLims.x) pos.x = posLims.x;
	else if (pos.x < -posLims.x) pos.x = -posLims.x;

	if (pos.z > posLims.z) pos.z = posLims.z;
	else if (pos.z < -posLims.z) pos.z = -posLims.z;
}

void Camera::MoveRight(float dt)
{
	if (xMove) pos.x += right.x * speed * dt;
	if (zMove) pos.z += right.z * speed * dt;

	if (pos.x > posLims.x) pos.x = posLims.x;
	else if (pos.x < -posLims.x) pos.x = -posLims.x;

	if (pos.z > posLims.z) pos.z = posLims.z;
	else if (pos.z < -posLims.z) pos.z = -posLims.z;
}

void Camera::RotateYaw(float value)
{
	yaw += value;
}

void Camera::RotatePitch(float value)
{
	pitch += value;

	if (pitch > maxPitch) pitch = maxPitch;
	if (pitch < -maxPitch) pitch = -maxPitch;
}
