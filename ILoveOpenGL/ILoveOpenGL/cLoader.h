#pragma once
#include <string>
#include <vector>
#include "cBasicTextureManager.h"
#include "cLevel.h"

class cLoader
{
public:
	std::vector<cLevel*> levels;

	void LoadTextureNames(cBasicTextureManager* manager);
	void SaveTextureNames(std::vector<std::string> texNames, cBasicTextureManager* manager);
	void LoadAllLevels();	
private:
	void LoadSpecificLevel(std::string levelFileName, cLevel* level);
};