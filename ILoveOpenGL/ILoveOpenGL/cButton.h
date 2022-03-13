#pragma once
#include "sPlataform.h"

// probably gonna inherit from entity or something
class cButton
{
public:
	glm::vec3 position;
	sPlataform* connectedPlataform;
	glm::vec3 plataformOgPosition;
	glm::vec3 plataformAlternatePosition;
};