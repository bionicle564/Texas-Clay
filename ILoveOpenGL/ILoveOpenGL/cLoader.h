#pragma once
#include <string>
#include <vector>
#include "cBasicTextureManager.h"

class cLoader
{
public:

	void LoadTextureNames(cBasicTextureManager* manager);
	void SaveTextureNames(std::vector<std::string> texNames, cBasicTextureManager* manager);

};