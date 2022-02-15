#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	bool isJumping;
	
	//float jumpOffset;
	float verticalSpeed;
	float gravity;

	float speed;

	Player(cMesh* mesh);
	~Player();

	void Update(float deltaTime);

	void MoveFoward();
	void MoveRight();
	void MoveLeft();
	void MoveBackward();
	void Jump();
};