#include "DebugMarker.h"

DebugMarker::DebugMarker(/*cMesh mesh*/) {
	//debugMesh = mesh;
	targetingLights = false;
	lightIndex = 0;
	modelIndex = 0;
}

DebugMarker::~DebugMarker() {
	//delete debugMesh;
}

void DebugMarker::SwitchTargetType() {
	targetingLights = !targetingLights;
}

void DebugMarker::UpdateLocation(glm::vec4 pos) {
	debugMesh->positionXYZ.x = pos.x;
	debugMesh->positionXYZ.y = pos.y;
	debugMesh->positionXYZ.z = pos.z;
}
