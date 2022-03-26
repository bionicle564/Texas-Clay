#include "PlatformEntity.h"

PlatformEntity::PlatformEntity(cMesh* mesh, float width, float length) : Entity(mesh) {
	this->width = width; 
	this->length = length; 


	mesh->scale.x = width / 10.0f;
	mesh->scale.z = length / 10.0f;

	behaviour = PLATFORM_STATIONARY;
	origin = mesh->positionXYZ;

	timer = 0.0f;
	resetTime = 2.0f;

	moveTimer = 0.0f;
	moveTime = 3.0f;

	isMoving = false;
	isMovingBack = false;
}

PlatformEntity::~PlatformEntity() {

}

void PlatformEntity::Process(float deltaTime) {
	if (behaviour == PLATFORM_STATIONARY) {
		if (isMoving) {
			timer += deltaTime;

			mesh->positionXYZ = origin + (target * timer);

			if (timer >= 1.0f) {
				timer = 1.0f;
				mesh->positionXYZ = origin + (target * timer);
				isMoving = false;
				timer = 0.0f;
			}
		}
	}
	else if (behaviour == PLATFORM_MOVING) {
		if (!isMoving) {
			timer += deltaTime;
			if (timer >= resetTime) {
				timer = 0.0f;
				isMoving = true;
			}
		}
		else {
			moveTimer += deltaTime;

			float timePos = moveTimer / moveTime;

			if (timePos > 1.0f) { timePos = 1.0f; }

			if (isMovingBack) {
				mesh->positionXYZ = origin + (-target * timePos);
			}
			else {
				mesh->positionXYZ = origin + (target * timePos);
			}

			if (timePos >= 1.0f) {
				/*moveTimer = moveTime;
				if (isMovingBack) {
					mesh->positionXYZ = origin + (-target * moveTimer);
				}
				else {
					mesh->positionXYZ = origin + (target * moveTimer);
				}*/
				origin = mesh->positionXYZ;
				isMovingBack = !isMovingBack;
				timer = 0.0f;
				moveTimer = 0.0f;
			}
		}
	}
}