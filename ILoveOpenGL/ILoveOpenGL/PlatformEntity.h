#pragma once

#include "Entity.h"

class PlatformEntity : public Entity {
public:
	bool isMoving;

	int id;
	float width; // x
	float length; // z

	PlatformEntity(cMesh* mesh, float width, float length);
	~PlatformEntity();
private:

};