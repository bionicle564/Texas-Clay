#pragma once

#include "Player.h"
#include "PlatformEntity.h"
#include "ButtonEntity.h"
#include "TreasureEntity.h"
#include "cLoader.h"

class SceneManager
{
public:
	SceneManager(Player* player);
	~SceneManager();

	void RegisterPlatform(PlatformEntity* platform);
	void LoadTextures(cBasicTextureManager* manager); //Why is this here?

	//maybe make all these return sucess bools?
	void SetUpLevel(int levelIndex);
	void CopyOverWorldEntities(std::vector<Entity*>& world);
	void CopyOverSpriteEntities(std::vector<Entity*>& sprites);

	void Process();

	bool UseButton(int buttonIndex);

private:
	Player* player;

	cLoader loader;

	std::vector<PlatformEntity*> platforms;
	std::vector<ButtonEntity*> buttons;
	std::vector<TreasureEntity*> treasures;
};

