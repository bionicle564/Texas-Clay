#include "TreasureEntity.h"

#include <iostream>

TreasureEntity::TreasureEntity(cMesh* mesh, float captureRadius, Player* player) : Entity(mesh) {
	this->player = player;
	this->captureRadius = captureRadius;
}

TreasureEntity::~TreasureEntity() {

}

void TreasureEntity::Process() {
	float distance = glm::distance(mesh->positionXYZ, player->mesh->positionXYZ);
	distance = fabsf(distance);

	if (distance < captureRadius) {
		std::cout << "playing: Fanfare.ogg" << std::endl;
		std::cout << "A Winner is YOU" << std::endl;
	}
}