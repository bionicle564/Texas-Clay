#include "SceneManager.h";

SceneManager::SceneManager(Player* player)
{
	this->player = player;

	isSceneDone = false;

	//good enough for now
	cMesh* treasure = new cMesh();
	treasure->meshName = "SpriteHolder.ply";
	treasure->scale = glm::vec3(0.5f);
	treasure->positionXYZ = glm::vec3(0.0f, 1.0f, 0.0f);
	treasure->orientationXYZ.y = -1.57f;
	treasure->orientationXYZ.x = -1.57f;
	treasure->bDontLight = true;
	treasure->textureNames[0] = "Crown.bmp";
	treasure->textureRatios[0] = 1.0f;

	TreasureEntity* treasureEntity = new TreasureEntity(treasure, 0.5f, player);
	treasureEntity->isMainTreasure = true;
	treasures.push_back(treasureEntity);
	//good enough end

	loader.LoadAllLevels();
}

SceneManager::~SceneManager()
{
}

void SceneManager::RegisterPlatform(PlatformEntity* platform) {
	platforms.push_back(platform);
}

void SceneManager::LoadTextures(cBasicTextureManager* manager) {
	loader.LoadTextureNames(manager);
}

void SceneManager::SetUpLevel(int levelIndex) {
	if (levelIndex >= loader.levels.size()) { return; }

	isSceneDone = false;

	cLevel* level = loader.levels[levelIndex];

	for (int i = 0; i < level->plataforms.size(); i++) {
		platforms.push_back(level->plataforms[i]);
	}

	for (int i = 0; i < level->buttons.size(); i++) {
		buttons.push_back(level->buttons[i]);
		buttons[i]->SetPlayerReference(player);
	}

	player->mesh->positionXYZ = level->spawnPosition;
	spawn = level->spawnPosition;
	treasures[0]->mesh->positionXYZ = level->goalPosition;
}

void SceneManager::CleanUpLevel() {
	isSceneDone = false;

	for (int i = platforms.size() - 1; i >= 0; i--) {
		delete platforms[i];
		platforms[i] = 0;
	}
	platforms.clear(); //is this part nessacary?

	for (int i = buttons.size() - 1; i >= 0; i--) {
		delete buttons[i];
		buttons[i] = 0;
	}
	buttons.clear();

	for (int i = 0; i < treasures.size(); i++) {
		if (treasures[i]->isMainTreasure ) {
			treasures[i]->isCaptured = false;
		}
	}
}

void SceneManager::CopyOverWorldEntities(std::vector<Entity*>& world) {
	for (int i = 0; i < platforms.size(); i++) {
		world.push_back(platforms[i]);
	}
}

void SceneManager::CopyOverSpriteEntities(std::vector<Entity*>& sprites) {
	for (int i = 0; i < treasures.size(); i++) {
		sprites.push_back(treasures[i]);
	}
	for (int i = 0; i < buttons.size(); i++) {
		sprites.push_back(buttons[i]);
	}
}

void SceneManager::Process(float deltaTime) {
	//check for player falling
	bool isOnPlatform = false;
	//player->isAirBorne = true;
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
			if (distanceFromPlataform <= 0.2f && distanceFromPlataform >= -0.0f)
			{
				player->mesh->positionXYZ.y = platforms[i]->mesh->positionXYZ.y;
				player->verticalSpeed = 0.0f;
				player->isAirBorne = false;
				break;
			}
			
		}
	}
	for (int i = 0; i < platforms.size(); i++) { //why do I have to do this again? who the hell knows
		float maxX = platforms[i]->mesh->positionXYZ.x + (platforms[i]->width / 2.0f);
		float minX = platforms[i]->mesh->positionXYZ.x - (platforms[i]->width / 2.0f);
		float maxZ = platforms[i]->mesh->positionXYZ.z + (platforms[i]->length / 2.0f);
		float minZ = platforms[i]->mesh->positionXYZ.z - (platforms[i]->length / 2.0f);

		if ((player->mesh->positionXYZ.x <= maxX && player->mesh->positionXYZ.x >= minX)
			&& (player->mesh->positionXYZ.z <= maxZ && player->mesh->positionXYZ.z >= minZ)) { //if the player is over this platform
			isOnPlatform = true;
			break;
		}

	}
	if (!isOnPlatform) {
		player->isAirBorne = true;
	}

	player->Process(deltaTime);

	for (int i = 0; i < platforms.size(); i++) {
		platforms[i]->Process(deltaTime);
	}
	for (int i = 0; i < treasures.size(); i++) {
		treasures[i]->Process(deltaTime);
		if (treasures[i]->isMainTreasure && treasures[i]->isCaptured) {
			isSceneDone = true;
		}
	}
	for (int i = 0; i < buttons.size(); i++) {
		buttons[i]->Process(deltaTime);
	}

	if (player->mesh->positionXYZ.y < 0.0f) {
		player->mesh->positionXYZ = spawn;
		player->isAirBorne = false;
	}
}

void SceneManager::PlayerInteract() {
	//find what the player is interacting with
	int index = -1;
	float closestDistance = 100.0f; //an unreasonable amount;
	for (int i = 0; i < buttons.size(); i++) {
		
		if (buttons[i]->GetPlayerInteractable()) {
			float buttonDistance = buttons[i]->CalcButtonDistance();
			if (buttonDistance < closestDistance) {
				index = i;
				closestDistance = buttonDistance;
			}
		}

	}
	if (index >= 0) {
		UseButton(index);
	}
}

bool SceneManager::UseButton(int buttonIndex) {
	if (buttonIndex >= buttons.size()) { return false; }

	ButtonEntity* button = buttons[buttonIndex];

	if (!button->isPressed) {
		button->isPressed = true;
		button->mesh->textureNames[0] = "ButtonDown.bmp";
		int index = button->platformIndex;
		
		if (button->behaviour == BUTTON_MOVE) {
			if (!platforms[index]->isMoving) {

				if (button->moved) {
					platforms[index]->origin = platforms[index]->mesh->positionXYZ;
					platforms[index]->target = -button->offset;
				}
				else {
					platforms[index]->origin = platforms[index]->mesh->positionXYZ;
					platforms[index]->target = button->offset;
				}
				platforms[index]->isMoving = true;
			}
			button->moved = !button->moved;
		}
		else if (button->behaviour == BUTTON_PAUSE) {
			if (platforms[index]->isMoving) {
				platforms[index]->isMoving = false;
			}
		}
	}

	return false;
}