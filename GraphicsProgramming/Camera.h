#pragma once

#include "Vector3.h"
#include "Input.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Init(float speed, Vector3 startPos, Vector3 limits, bool xMove, bool yMove, bool zMove);
	void InitOrbital(Vector3 target, float radius, float orbitHeight, float speed);
	void InitStatic(Vector3 pos);

	void HandleInput(Input *input, float dt, int width, int height);

	void Update(float dt);

	void MoveForward(float dt);
	void MoveBackward(float dt);
	void MoveUp(float dt);
	void MoveDown(float dt);
	void MoveLeft(float dt);
	void MoveRight(float dt);
	void RotateYaw(float value);
	void RotatePitch(float value);

	#pragma region Getters & Setters

	#pragma region Getters
	Vector3 GetPosition() { return pos; };
	Vector3 GetLookAt() { return lookAt; };
	Vector3 GetUp() { return up; };

	float GetPosX() { return pos.x; };
	float GetLookAtX() { return lookAt.x; };
	float GetUpX() { return up.x; };

	float GetPosY() { return pos.y; };
	float GetLookAtY() { return lookAt.y; };
	float GetUpY() { return up.y; };

	float GetPosZ() { return pos.z; };
	float GetLookAtZ() { return lookAt.z; };
	float GetUpZ() { return up.z; };
	#pragma endregion

	#pragma region Setters
	void SetPosition(Vector3 value) { pos = value; };
	void SetLookAt(Vector3 value) { lookAt = value; };
	void SetUp(Vector3 value) { up = value; };

	void SetPosX(float value) { pos.x = value; };
	void SetLookAtX(float value) { lookAt.x = value; };
	void SetUpX(float value) { up.x = value; };

	void SetPosY(float value) { pos.y = value; };
	void SetLookAtY(float value) { lookAt.y = value; };
	void SetUpY(float value) { up.y = value; };

	void SetPosZ(float value) { pos.z = value; };
	void SetLookAtZ(float value) { lookAt.z = value; };
	void SetUpZ(float value) { up.z = value; };

	void SetYaw(float value) { yaw = value; };
	void SetPitch(float value) { pitch = value; };
	void SetRoll(float value) { roll = value; };
	#pragma endregion
	#pragma endregion

private:
	Vector3 pos = Vector3(0, 2, 0);
	Vector3 posLims;	//Limits to position essentially creating invisible bounding wall to keep cameras within
	Vector3 orbitTarget;
	Vector3 lookAt;
	Vector3 forward;
	Vector3 right;
	Vector3 up;

	bool xMove = true, yMove = true, zMove = true;
	bool orbital;
	bool staticCam;
	int maxPitch = 90;
	int startDelay = 0;

	float yaw = 0, pitch = 0, roll = 0;
	float speed = 5;
	float orbitTheta = 0;
	float orbitHeight = 0;
	float orbitRadius = 0;
};

