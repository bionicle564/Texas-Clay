#include "ButtonEntity.h"

ButtonEntity::ButtonEntity(cMesh* mesh, glm::vec3 offset, int platformIndex) : Entity(mesh) {
	this->platformIndex = platformIndex;
	this->offset = offset;

	isPressed = false;
	moved = false;
}

ButtonEntity::~ButtonEntity() {

}