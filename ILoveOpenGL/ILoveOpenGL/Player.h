#pragma once

#include "Entity.h"

class Player : public Entity {
public:
	bool jumpingUp;
	
	float jumpOffset;

	float speed;

	Player(cMesh* mesh);
	~Player();

	void Update();

	void MoveFoward();
	void MoveRight();
	void MoveLeft();
	void MoveBackward();
	void Jump();

};