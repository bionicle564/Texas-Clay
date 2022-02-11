#pragma once

#include "Mesh.h"

class DebugMarker {
public:
	bool targetingLights;

	int lightIndex;
	int modelIndex;

	cMesh* debugMesh;
	
	DebugMarker(/*cMesh mesh*/);
	~DebugMarker();

	void SwitchTargetType();
	void UpdateLocation(glm::vec4 pos);
};