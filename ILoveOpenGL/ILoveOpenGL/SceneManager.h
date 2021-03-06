#pragma once

#include "Player.h"
#include "PlatformEntity.h"
#include "ButtonEntity.h"
#include "TreasureEntity.h"
#include "cLoader.h"

class SceneManager
{
public:
	bool isSceneDone;

	SceneManager(Player* player);
	~SceneManager();

	void RegisterPlatform(PlatformEntity* platform);
	void LoadTextures(cBasicTextureManager* manager); //Why is this here?

	//maybe make all these return sucess bools?
	void SetUpLevel(int levelIndex);
	void CleanUpLevel();
	void CopyOverWorldEntities(std::vector<Entity*>& world);
	void CopyOverSpriteEntities(std::vector<Entity*>& sprites);

	void Process(float deltaTime);

	void PlayerInteract();

private:
	glm::vec3 spawn;
	
	Player* player;

	cLoader loader;

	std::vector<PlatformEntity*> platforms;
	std::vector<ButtonEntity*> buttons;
	std::vector<TreasureEntity*> treasures;

	bool UseButton(int buttonIndex);
};

