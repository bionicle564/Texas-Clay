#include "Player.h"

#include <glm/gtx/euler_angles.hpp>
#include <iostream>

Player::Player(cMesh* mesh) : Entity(mesh) {
	isJumping = false;

	verticalSpeed = 0.0f;
	gravity = -9.8f;

	speed = 2.25f;
}

Player::~Player() {

}

void Player::Update(float deltaTime) 
{
	//if (jumpingUp) {
	//	mesh->positionXYZ.y += speed * 0.03f;
	//	jumpOffset += speed * 0.03f;
	//	if (jumpOffset >= speed) {
	//		jumpingUp = false;
	//	}
	//}
	//else if (jumpOffset > 0.0f) {
	//	mesh->positionXYZ.y -= speed * 0.03f;
	//	jumpOffset -= speed * 0.03f;
	//	if (jumpOffset < 0.0f) {
	//		mesh->positionXYZ.y = 0.0f;
	//		jumpOffset = 0.0f;
	//	}
	//}
	
	if (isJumping)
	{
		mesh->positionXYZ.y += verticalSpeed * deltaTime;
		verticalSpeed += gravity * deltaTime;

		if (mesh->positionXYZ.y <= 0.f)
		{
			mesh->positionXYZ.y = 0.f;
			verticalSpeed = 0.f;
			isJumping = false;
		}

		std::cout << "POSITION: " << mesh->positionXYZ.y << std::endl;
		std::cout << "SPEED: " << verticalSpeed << std::endl;
	}
	//else
	//{

	//}
}

void Player::MoveFoward() {

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
}

void Player::MoveRight() {
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

void Player::MoveLeft() {
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

void Player::MoveBackward() {
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
}

void Player::Jump() 
{
	//if (!jumpingUp && jumpOffset <= 0.0f) {
	//	jumpingUp = true;
	//}
	std::cout << "JUMP" << std::endl;

	if (!isJumping)
	{
		verticalSpeed = 5.f;
		isJumping = true;
	}
}