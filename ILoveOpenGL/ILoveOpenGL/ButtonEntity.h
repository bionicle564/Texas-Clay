#pragma once

#include "Entity.h"
#include "Player.h"

enum ButtonBehaviour {
	BUTTON_MOVE = 0, //Use with STATIONARY platforms
	BUTTON_PAUSE = 1 //Use with MOVING platforms
};

class ButtonEntity : public Entity {
public:
	bool isPressed;
	bool moved;

	int platformIndex;

	float interactRadius;
	float buttonTimer;
	float resetTime; //default 2.0f (2 seconds), you might want to increase this for a pause button

	ButtonBehaviour behaviour;

	glm::vec3 offset;

	ButtonEntity(cMesh* mesh, float radius, glm::vec3 offset, int platformIndex);
	~ButtonEntity();

	void SetPlayerReference(Player* player);

	void Process(float deltaTime);

	bool GetPlayerInteractable();
	float CalcButtonDistance();

private:
	Player* player;
};