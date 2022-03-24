#include "Entity.h";

Entity::Entity(cMesh* mesh) {
	executing = false;
	this->mesh = mesh;

	facing = FACING_DOWN;
}

Entity::~Entity() {
	delete mesh;
}


void Entity::Process(float deltaTime) {
	
}

