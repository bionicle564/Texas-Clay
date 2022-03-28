
// This represents a single mesh object we are drawing
#include "Mesh.h"

cMesh::cMesh()
{
	this->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	this->orientationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);

	this->scale = glm::vec3(1.0f);

	this->bIsWireframe = false;

	render = true;

	this->objectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);	// White
	this->bUseObjectDebugColour = false;
	this->bDontLight = false;

	this->bUseWholeObjectDiffuseColour = false;
	this->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);	// The "colour" of the object
	this->wholeObjectSpecularRGB = glm::vec3(1.0f, 1.0f, 1.0f);

	this->wholeObjectShininess_SpecPower = 1.0f;	// 1.0 to ??

	//Or you could do this
//	this->positionXYZ.x = 0.0f;
//	this->positionXYZ.y = 0.0f;
//	this->positionXYZ.z = 0.0f;
	// etc...

	this->alphaTransparency = 1.0f;

	// Clear all the textures
	for (unsigned int index = 0; index != cMesh::MAX_TEXTURES; index++)
	{
		this->textureNames[index] = "";
		this->textureRatios[index] = 0.0f;
	}
	//this->textureNames[0] = "wood.bmp";
	//this->textureRatios[0] = 1.0f;

}

void cMesh::clearTextureRatiosToZero(void)
{
	for (unsigned int index = 0; index != cMesh::MAX_TEXTURES; index++)
	{
		this->textureRatios[index] = 0.0f;
	}
	return;
}