#pragma once

#include "Player.h"

class TreasureEntity : public Entity {
public:
	bool isMainTreasure;
	bool isCaptured;

	float captureRadius;

	Player* player;

	TreasureEntity(cMesh* mesh);
	~TreasureEntity();

	void Process(float deltaTime);

	void SetPlayerReference(Player* player);

};

