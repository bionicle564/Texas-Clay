#pragma once
#include <glm/ext/vector_float3.hpp>

// probably gonna change this to inherit from entity to have a mesh and etc
struct sPlataform
{
	int id;
	glm::vec3 position;
	float width; // x
	float length; // z
};