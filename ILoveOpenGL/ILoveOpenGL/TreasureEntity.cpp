#include "TreasureEntity.h"

#include <iostream>

TreasureEntity::TreasureEntity(cMesh* mesh) : Entity(mesh) {
	this->player = player;
	
	captureRadius = 0.5f;

	isMainTreasure = false;
	isCaptured = false;
}

TreasureEntity::~TreasureEntity() {

}

void TreasureEntity::Process(float deltaTime) {
	float distance = glm::distance(mesh->positionXYZ, player->mesh->positionXYZ);
	distance = fabsf(distance);

	if (distance < captureRadius && !isCaptured) {
		isCaptured = true;
		mesh->render = false;
		if (isMainTreasure) {
			std::cout << "playing: Fanfare.ogg" << std::endl;
			std::cout << "A Winner is YOU" << std::endl;
		}
		else {
			std::cout << "+1 super guy points" << std::endl;
		}
	}

}

void TreasureEntity::SetPlayerReference(Player* player) {
	this->player = player;
}