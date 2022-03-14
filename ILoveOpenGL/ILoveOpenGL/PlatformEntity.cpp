#include "PlatformEntity.h"

PlatformEntity::PlatformEntity(cMesh* mesh, float width, float length) : Entity(mesh) {
	this->width = width;
	this->length = length;
}

PlatformEntity::~PlatformEntity() {

}