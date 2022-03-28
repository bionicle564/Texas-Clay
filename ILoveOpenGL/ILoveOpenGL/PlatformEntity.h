#pragma once

#include "Entity.h"

enum PlatformBehaviour {
	PLATFORM_STATIONARY = 0, //default platform, will only move if a button pushes it
	PLATFORM_MOVING = 1
};

class PlatformEntity : public Entity {
public:
	bool isMoving;
	bool isMovingBack;

	int id;
	float width; // x
	float length; // z

	float timer;
	float resetTime;

	float moveTimer;
	float moveTime;

	PlatformBehaviour behaviour;

	glm::vec3 origin;
	glm::vec3 target;

	PlatformEntity(cMesh* mesh, float width, float length);
	~PlatformEntity();

	void Process(float deltaTime);

private:

};