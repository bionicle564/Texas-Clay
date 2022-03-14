#pragma once

#include "Entity.h"

class ButtonEntity : public Entity {
public:
	bool isPressed;
	bool moved;

	int platformIndex;

	glm::vec3 offset;

	ButtonEntity(cMesh* mesh, glm::vec3 offset, int platformIndex);
	~ButtonEntity();
};