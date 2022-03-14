#pragma once

#include "Player.h"
#include "PlatformEntity.h"
#include "cLoader.h"

class SceneManager
{
public:
	SceneManager(Player* player);
	~SceneManager();

	void RegisterPlatform(PlatformEntity* platform);

	void Process();

private:
	Player* player;

	cLoader Loader;

	std::vector<PlatformEntity*> platforms;
};

