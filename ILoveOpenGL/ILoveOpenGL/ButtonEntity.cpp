#include "ButtonEntity.h"

ButtonEntity::ButtonEntity(cMesh* mesh, float radius, glm::vec3 offset, int platformIndex) : Entity(mesh) {
	this->platformIndex = platformIndex;
	this->offset = offset;

	this->interactRadius = radius;
	behaviour = BUTTON_MOVE;

	buttonTimer = 0.0f;
	resetTime = 2.0f;

	isPressed = false;
	moved = false;
}

ButtonEntity::~ButtonEntity() {

}

void ButtonEntity::SetPlayerReference(Player* player) {
	this->player = player;
}

void ButtonEntity::Process(float deltaTime) {
	if (isPressed) {
		buttonTimer += deltaTime;
		if (buttonTimer >= resetTime) {
			buttonTimer = 0.0f;
			isPressed = false;
			mesh->textureNames[0] = "ButtonUp.bmp";
		}
	}
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