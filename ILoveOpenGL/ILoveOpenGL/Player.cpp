#include "Player.h"

#include <glm/gtx/euler_angles.hpp>
#include <iostream>

Player::Player(cMesh* mesh) : Entity(mesh) 
{
	isOnAir = false;
	verticalSpeed = 0.0f;
	gravity = -9.8f;

	speed = 2.25f;

	hasMoved = false;
	moveTimer = 0.0f;

	Floor plat1;
	plat1.position = glm::vec3(0.f, 10.f, 0.f);
	plat1.width = 10.f;
	plat1.length = 10.f;
	plataforms.push_back(plat1);

	Floor plat2;
	plat2.position = glm::vec3(5.f, 0.f, 0.f);
	plat2.width = 10.f;
	plat2.length = 10.f;
	plataforms.push_back(plat2);
}

Player::~Player() 
{

}

void Player::Update(float deltaTime) 
{	
	//std::cout << "POSITION: " << mesh->positionXYZ.x << ", " << mesh->positionXYZ.y << ", " << mesh->positionXYZ.z << std::endl;
	//std::cout << "SPEED: " << verticalSpeed << std::endl;

	if (!hasMoved) {
		moveTimer = 0.0f;
		mesh->textureNames[0] = "TexasClayFront1.bmp";
	}
	else {
		moveTimer += deltaTime;
		if (moveTimer < 0.15f) {
			mesh->textureNames[0] = "TexasClayFront1.bmp";
		}
		else if (moveTimer < 0.3f) {
			mesh->textureNames[0] = "TexasClayFront2.bmp";
		}
		else if (moveTimer < 0.45f) {
			mesh->textureNames[0] = "TexasClayFront1.bmp";
		}
		else if (moveTimer < 0.6f) {
			mesh->textureNames[0] = "TexasClayFront3.bmp";
		}
		else {
			moveTimer = 0.0f;
		}
		//hasMoved = false;
	}

	for (int i = 0; i < plataforms.size(); i++)
	{
		float maxX = plataforms[i].position.x + (plataforms[i].width / 2);
		float minX = plataforms[i].position.x - (plataforms[i].width / 2);
		float maxZ = plataforms[i].position.z + (plataforms[i].length / 2);
		float minZ = plataforms[i].position.z - (plataforms[i].length / 2);

		if ((mesh->positionXYZ.x <= maxX && mesh->positionXYZ.x >= minX) && (mesh->positionXYZ.z <= maxZ && mesh->positionXYZ.z >= minZ) && verticalSpeed < 0.f)
		{
			float distanceFromPlataform = mesh->positionXYZ.y - plataforms[i].position.y;
			if (distanceFromPlataform <= 0.2f && distanceFromPlataform >= 0.f)
			{
				mesh->positionXYZ.y = plataforms[i].position.y;
				verticalSpeed = 0.f;
				isOnAir = false;
				break;
			}
		}

		isOnAir = true;
	}

	if (isOnAir)
	{
		mesh->positionXYZ.y += verticalSpeed * deltaTime;
		verticalSpeed += gravity * deltaTime;
	}
	//else
	//{

	//}
}

void Player::MoveFoward() 
{

	//A bunch of math we gotta do to make the particle go the right direction
	//cannon defaults to face absolute Z (even it if it's state is loaded in, it's relative to this)
	glm::vec4 defaultDirection = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	//A matrix that represents euler angle values of the head's rotation
	glm::mat4x4 eulerOrientationMatrix = glm::eulerAngleXYZ(mesh->orientationXYZ.x + 1.57f, mesh->orientationXYZ.y + 1.57f, mesh->orientationXYZ.z);
	//make the orientation relative to absolution direction
	eulerOrientationMatrix *= defaultDirection;
	//we're in 3 dimesions so we want x, y, and z
	//this also has to be a vec4, or else the last line won't compile.
	glm::vec4 usefulDirections = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	//pull out the directions we want into a vec3
	glm::vec3 direction = glm::vec3(usefulDirections * eulerOrientationMatrix);

	direction.x *= -1.0f;
	/*glm::vec3 direction(0.0f); 
	direction.x = mesh->orientationXYZ.x + 1.57f;
	direction.y = mesh->orientationXYZ.y + 1.57f;
	direction.z = mesh->orientationXYZ.z;

	direction -= glm::vec3(0.0f, 0.0f, -1.0f);

	direction = glm::normalize(direction);*/

	glm::vec3 movement = direction * (speed * 0.03f);

	mesh->positionXYZ += movement;

	hasMoved = true;
}

void Player::MoveRight() 
{
	//A bunch of math we gotta do to make the particle go the right direction
	//cannon defaults to face absolute Z (even it if it's state is loaded in, it's relative to this)
	glm::vec4 defaultDirection = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	//A matrix that represents euler angle values of the head's rotation
	glm::mat4x4 eulerOrientationMatrix = glm::eulerAngleXYZ(mesh->orientationXYZ.x + 1.57f, mesh->orientationXYZ.y + 1.57f, mesh->orientationXYZ.z);
	//make the orientation relative to absolution direction
	eulerOrientationMatrix *= defaultDirection;
	//we're in 3 dimesions so we want x, y, and z
	//this also has to be a vec4, or else the last line won't compile.
	glm::vec4 usefulDirections = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	//pull out the directions we want into a vec3
	glm::vec3 direction = glm::vec3(usefulDirections * eulerOrientationMatrix);

	direction.x *= -1.0f;

	glm::vec3 vecLeft = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));

	//glm::vec3 vecAmountToMove = glm::normalize(vecLeft) * amount;
	glm::vec3 movement = glm::normalize(vecLeft) * (speed * 0.03f);

	mesh->positionXYZ += movement;
}

void Player::MoveLeft() 
{
	//A bunch of math we gotta do to make the particle go the right direction
	//cannon defaults to face absolute Z (even it if it's state is loaded in, it's relative to this)
	glm::vec4 defaultDirection = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	//A matrix that represents euler angle values of the head's rotation
	glm::mat4x4 eulerOrientationMatrix = glm::eulerAngleXYZ(mesh->orientationXYZ.x + 1.57f, mesh->orientationXYZ.y + 1.57f, mesh->orientationXYZ.z);
	//make the orientation relative to absolution direction
	eulerOrientationMatrix *= defaultDirection;
	//we're in 3 dimesions so we want x, y, and z
	//this also has to be a vec4, or else the last line won't compile.
	glm::vec4 usefulDirections = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	//pull out the directions we want into a vec3
	glm::vec3 direction = glm::vec3(usefulDirections * eulerOrientationMatrix);

	direction.x *= -1.0f;

	glm::vec3 vecLeft = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));

	//glm::vec3 vecAmountToMove = glm::normalize(vecLeft) * amount;
	glm::vec3 movement = glm::normalize(vecLeft) * (speed * 0.03f);
	
	mesh->positionXYZ -= movement;

	//mesh->positionXYZ.x += speed * 0.03f;
}

void Player::MoveBackward() 
{
	//A bunch of math we gotta do to make the particle go the right direction
	//cannon defaults to face absolute Z (even it if it's state is loaded in, it's relative to this)
	glm::vec4 defaultDirection = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	//A matrix that represents euler angle values of the head's rotation
	glm::mat4x4 eulerOrientationMatrix = glm::eulerAngleXYZ(mesh->orientationXYZ.x + 1.57f, mesh->orientationXYZ.y + 1.57f, mesh->orientationXYZ.z);
	//make the orientation relative to absolution direction
	eulerOrientationMatrix *= defaultDirection;
	//we're in 3 dimesions so we want x, y, and z
	//this also has to be a vec4, or else the last line won't compile.
	glm::vec4 usefulDirections = glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
	//pull out the directions we want into a vec3
	glm::vec3 direction = glm::vec3(usefulDirections * eulerOrientationMatrix);

	direction.x *= -1.0f;
	/*glm::vec3 direction(0.0f);
	direction.x = mesh->orientationXYZ.x + 1.57f;
	direction.y = mesh->orientationXYZ.y + 1.57f;
	direction.z = mesh->orientationXYZ.z;

	direction -= glm::vec3(0.0f, 0.0f, -1.0f);

	direction = glm::normalize(direction);*/

	glm::vec3 movement = direction * (speed * 0.03f);

	mesh->positionXYZ -= movement;

	hasMoved = true;
}

void Player::Jump() 
{
	//if (!jumpingUp && jumpOffset <= 0.0f) {
	//	jumpingUp = true;
	//}
	std::cout << "JUMP" << std::endl;

	if (!isOnAir)
	{
		verticalSpeed = 5.f;
		isOnAir = true;
	}
}