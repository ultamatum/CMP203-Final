#include "Camera.h"

Camera::Camera() {}

Camera::~Camera() {}

void Camera::Update()
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

void Camera::MoveForward(float dt, float speed)
{
	pos.x += (forward.x * speed) * dt;
	pos.y += (forward.y * speed) * dt;
	pos.z += (forward.z * speed) * dt;
}

void Camera::MoveBackward(float dt, float speed)
{
	pos.x -= (forward.x * speed) * dt;
	pos.y -= (forward.y * speed) * dt;
	pos.z -= (forward.z * speed) * dt;
}

void Camera::MoveUp(float dt)
{
	pos.y += up.y * dt;
}

void Camera::MoveDown(float dt)
{
	pos.y -= up.y * dt;
}

void Camera::MoveLeft(float dt, float speed)
{
	pos.x -= right.x * speed * dt;
	pos.z -= right.z * speed * dt;
}

void Camera::MoveRight(float dt, float speed)
{
	pos.x += right.x * speed * dt;
	pos.z += right.z * speed * dt;
}

void Camera::RotateYaw(float value)
{
	yaw += value;
}

void Camera::RotatePitch(float value)
{
	pitch += value;

	if (pitch > 90) pitch = 90;
	if (pitch < -90) pitch = -90;
}
