#pragma once
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include "PlatformEntity.h"
#include "ButtonEntity.h"
//#include "sPlataform.h"
//#include "cButton.h"

class cLevel
{
public:

	glm::vec3 spawnPosition;
	glm::vec3 goalPosition;
	//glm::vec3 treasurePosition;
	//std::vector<sPlataform> plataforms;
	//std::vector<cButton> buttons;

	std::vector<PlatformEntity> plataforms;
	std::vector<ButtonEntity> buttons;
};