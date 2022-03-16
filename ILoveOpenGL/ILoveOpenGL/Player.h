#pragma once

#include "Entity.h"
//struct Floor
//{
//	glm::vec3 position;
//	float width; // x
//	float length; // z
//};

class Player : public Entity {
public:
	bool isAirBorne;
	float verticalSpeed;
	float gravity;

	bool hasMoved;
	float moveTimer;

	//std::vector<Floor> plataforms;

	float speed;

	Player(cMesh* mesh);
	~Player();

	void Update(float deltaTime);

	void MoveFoward();
	void MoveRight();
	void MoveLeft();
	void MoveBackward();
	void Jump();
	//void SetIsAirborne(bool _isAirBorne);
	//glm::vec3 GetPosition();
	//void SetPosition(glm::vec3);
};