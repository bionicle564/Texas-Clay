#pragma once

#include "Player.h"

class TreasureEntity : public Entity {
public:
	float captureRadius;

	Player* player;

	TreasureEntity(cMesh* mesh, float captureRadius, Player* player);
	~TreasureEntity();

	void Process(float deltaTime);

};

