#include "Player.h"

#include <glm/gtx/euler_angles.hpp>
#include <iostream>

Player::Player(cMesh* mesh) : Entity(mesh) 
{
	isAirBorne = false;
	verticalSpeed = 0.0f;
	gravity = -9.8f;

	speed = 2.25f;

	hasMoved = false;
	moveTimer = 0.0f;



}

Player::~Player() 
{

}

void Player::Process(float deltaTime) 
{	
	//std::cout << "POSITION: " << mesh->positionXYZ.x << ", " << mesh->positionXYZ.y << ", " << mesh->positionXYZ.z << std::endl;
	//std::cout << "SPEED: " << verticalSpeed << std::endl;

	if (!hasMoved) {
		moveTimer = 0.0f;
		switch (facing)
		{
		case FACING_UP:
			mesh->textureNames[0] = "TexasClayBack1.bmp";
			break;
		case FACING_DOWN:
			mesh->textureNames[0] = "TexasClayFront1.bmp";
			break;
		case FACING_LEFT:
			mesh->textureNames[0] = "TexasClayLeft1.bmp";
			break;
		case FACING_RIGHT:
			mesh->textureNames[0] = "TexasClayRight1.bmp";
			break;
		}
	}
	else {
		moveTimer += deltaTime;
		if (moveTimer < 0.15f) {
			switch (facing)
			{
			case FACING_UP:
				mesh->textureNames[0] = "TexasClayBack1.bmp";
				break;
			case FACING_DOWN:
				mesh->textureNames[0] = "TexasClayFront1.bmp";
				break;
			case FACING_LEFT:
				mesh->textureNames[0] = "TexasClayLeft1.bmp";
				break;
			case FACING_RIGHT:
				mesh->textureNames[0] = "TexasClayRight1.bmp";
				break;
			}
		}
		else if (moveTimer < 0.3f) {
			switch (facing)
			{
			case FACING_UP:
				mesh->textureNames[0] = "TexasClayBack2.bmp";
				break;
			case FACING_DOWN:
				mesh->textureNames[0] = "TexasClayFront2.bmp";
				break;
			case FACING_LEFT:
				mesh->textureNames[0] = "TexasClayLeft2.bmp";
				break;
			case FACING_RIGHT:
				mesh->textureNames[0] = "TexasClayRight2.bmp";
				break;
			}
		}
		else if (moveTimer < 0.45f) {
			switch (facing)
			{
			case FACING_UP:
				mesh->textureNames[0] = "TexasClayBack1.bmp";
				break;
			case FACING_DOWN:
				mesh->textureNames[0] = "TexasClayFront1.bmp";
				break;
			case FACING_LEFT:
				mesh->textureNames[0] = "TexasClayLeft1.bmp";
				break;
			case FACING_RIGHT:
				mesh->textureNames[0] = "TexasClayRight1.bmp";
				break;
			}
		}
		else if (moveTimer < 0.6f) {
			switch (facing)
			{
			case FACING_UP:
				mesh->textureNames[0] = "TexasClayBack3.bmp";
				break;
			case FACING_DOWN:
				mesh->textureNames[0] = "TexasClayFront3.bmp";
				break;
			case FACING_LEFT:
				mesh->textureNames[0] = "TexasClayLeft3.bmp";
				break;
			case FACING_RIGHT:
				mesh->textureNames[0] = "TexasClayRight3.bmp";
				break;
			}
		}
		else {
			moveTimer = 0.0f;
		}
		hasMoved = false;
	}


	if (isAirBorne)
	{
		mesh->positionXYZ.y += verticalSpeed * deltaTime;
		verticalSpeed += gravity * deltaTime;
		if (verticalSpeed < 0.0f) {
			switch (facing)
			{
			case FACING_UP:
				mesh->textureNames[0] = "TexasClayBackFall.bmp";
				break;
			case FACING_DOWN:
				mesh->textureNames[0] = "TexasClayFrontFall.bmp";
				break;
			case FACING_LEFT:
				mesh->textureNames[0] = "TexasClayLeftFall.bmp";
				break;
			case FACING_RIGHT:
				mesh->textureNames[0] = "TexasClayRightFall.bmp";
				break;
			}
		}
		else if (verticalSpeed > 0.0f){
			switch (facing)
			{
			case FACING_UP:
				mesh->textureNames[0] = "TexasClayBackJump.bmp";
				break;
			case FACING_DOWN:
				mesh->textureNames[0] = "TexasClayFrontJump.bmp";
				break;
			case FACING_LEFT:
				mesh->textureNames[0] = "TexasClayLeftJump.bmp";
				break;
			case FACING_RIGHT:
				mesh->textureNames[0] = "TexasClayRightJump.bmp";
				break;
			}
		}
	}
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
	facing = FACING_UP;
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

	hasMoved = true;
	facing = FACING_RIGHT;
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

	hasMoved = true;
	facing = FACING_LEFT;
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
	facing = FACING_DOWN;
}

void Player::Jump() 
{
	//if (!jumpingUp && jumpOffset <= 0.0f) {
	//	jumpingUp = true;
	//}
	//std::cout << "JUMP" << std::endl;

	if (!isAirBorne)
	{
		verticalSpeed = 5.0f;
		isAirBorne = true;
	}
}

//void Player::SetIsAirborne(bool _isAirBorne)
//{
//	isAirBorne = _isAirBorne;
//}
//
//glm::vec3 Player::GetPosition()
//{
//	return mesh->positionXYZ;
//}
