#include "GameObject.h"

GameObject::GameObject() {}

GameObject::~GameObject(){}

//Default update method just to move object by it's current velocity (will only be used if collisions get implemented in time)
void GameObject::Update()
{
	position.x += velocity.x;
	position.y += velocity.y;
	position.z += velocity.z;
}
