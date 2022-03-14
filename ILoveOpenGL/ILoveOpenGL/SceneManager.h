#pragma once

#include "Player.h"
#include "PlatformEntity.h"
#include "ButtonEntity.h"
#include "cLoader.h"

class SceneManager
{
public:
	SceneManager(Player* player);
	~SceneManager();

	void RegisterPlatform(PlatformEntity* platform);

	void Process();

	bool UseButton(int buttonIndex);

private:
	Player* player;

	cLoader Loader;

	std::vector<PlatformEntity*> platforms;
	std::vector<ButtonEntity*> buttons;
};

