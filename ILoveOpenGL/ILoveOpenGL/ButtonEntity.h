#pragma once

#include "Entity.h"
#include "Player.h"

class ButtonEntity : public Entity {
public:
	bool isPressed;
	bool moved;

	int platformIndex;

	float interactRadius;

	glm::vec3 offset;

	ButtonEntity(cMesh* mesh, float radius, glm::vec3 offset, int platformIndex);
	~ButtonEntity();

	void SetPlayerReference(Player* player);

	bool GetPlayerInteractable();
	float CalcButtonDistance();

private:
	Player* player;
};