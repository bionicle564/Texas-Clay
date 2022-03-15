#include "ButtonEntity.h"

ButtonEntity::ButtonEntity(cMesh* mesh, float radius, glm::vec3 offset, int platformIndex) : Entity(mesh) {
	this->platformIndex = platformIndex;
	this->offset = offset;

	this->interactRadius = radius;

	isPressed = false;
	moved = false;
}

ButtonEntity::~ButtonEntity() {

}

void ButtonEntity::SetPlayerReference(Player* player) {
	this->player = player;
}

bool ButtonEntity::GetPlayerInteractable() {
	if (isPressed) { return false; }

	if (CalcButtonDistance() < interactRadius) {
		return true;
	}

	return false;
}

float ButtonEntity::CalcButtonDistance() {
	return glm::distance(player->mesh->positionXYZ, mesh->positionXYZ);
}