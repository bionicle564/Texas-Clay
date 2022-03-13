#pragma once
#include <string>
#include <vector>
#include "cBasicTextureManager.h"
#include "cLevel.h"

class cLoader
{
public:

	void LoadTextureNames(cBasicTextureManager* manager);
	void SaveTextureNames(std::vector<std::string> texNames, cBasicTextureManager* manager);
	void LoadAllLevels(std::vector<cLevel*>& levels);
	void LoadSpecificLevel(std::string levelFileName, cLevel* level);
};