#include "PlatformEntity.h"

PlatformEntity::PlatformEntity(cMesh* mesh, float width, float length) : Entity(mesh) {
	this->width = width; 
	this->length = length; 

	mesh->scale.x = width / 10.0f;
	mesh->scale.z = length / 10.0f;

	isMoving = false;
}

PlatformEntity::~PlatformEntity() {

}

void PlatformEntity::Process(float deltaTime) {

}