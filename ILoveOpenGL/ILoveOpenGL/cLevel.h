#pragma once
#include <glm/ext/vector_float3.hpp>
#include <vector>
#include "sPlataform.h"
#include "cButton.h"

class cLevel
{
public:

	glm::vec3 spawnPosition;
	glm::vec3 goalPosition;
	//glm::vec3 treasurePosition;
	std::vector<sPlataform> plataforms;
	std::vector<cButton> buttons;


};