#include "SceneManager.h";

SceneManager::SceneManager(Player* player)
{
	this->player = player;
}

SceneManager::~SceneManager()
{
}

void SceneManager::RegisterPlatform(PlatformEntity* platform) {
	platforms.push_back(platform);
}

void SceneManager::Process() {
	//check for player falling
	for (int i = 0; i < platforms.size(); i++) {
		float maxX = platforms[i]->mesh->positionXYZ.x + (platforms[i]->width / 2.0f);
		float minX = platforms[i]->mesh->positionXYZ.x - (platforms[i]->width / 2.0f);
		float maxZ = platforms[i]->mesh->positionXYZ.z + (platforms[i]->length / 2.0f);
		float minZ = platforms[i]->mesh->positionXYZ.z - (platforms[i]->length / 2.0f);

		if ((player->mesh->positionXYZ.x <= maxX && player->mesh->positionXYZ.x >= minX) 
			&& (player->mesh->positionXYZ.z <= maxZ && player->mesh->positionXYZ.z >= minZ) 
			&& player->verticalSpeed < 0.0f)
		{
			float distanceFromPlataform = player->mesh->positionXYZ.y - platforms[i]->mesh->positionXYZ.y;
			if (distanceFromPlataform <= 0.2f && distanceFromPlataform >= 0.0f)
			{
				player->mesh->positionXYZ.y = platforms[i]->mesh->positionXYZ.y;
				player->verticalSpeed = 0.0f;
				player->isAirBorne = false;
				break;
			}
		}

		player->isAirBorne = true;
	}
}

bool SceneManager::UseButton(int buttonIndex) {
	if (buttonIndex >= buttons.size()) { return false; }

	ButtonEntity* button = buttons[buttonIndex];

	if (!button->isPressed) {
		button->isPressed = true;
		int index = button->platformIndex;

		if (!platforms[index]->isMoving) {
			//TODO: make this change gradual
			if (button->moved) {
				platforms[index]->mesh->positionXYZ -= button->offset;
			}
			else {
				platforms[index]->mesh->positionXYZ += button->offset;
			}
		}
		button->moved = !button->moved;
	}

	return false;
}