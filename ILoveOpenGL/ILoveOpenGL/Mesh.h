#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class cMesh
{
public:
	cMesh();
	std::string meshName;
	std::string nameID;

	glm::vec3 positionXYZ;
	glm::vec3 orientationXYZ;		// "angle"
	glm::vec3 scale;

	// Sets the overall colour of the object
	//	by overwriting the colour variable
	// HACK: We'll get rid of this once we have textures
	glm::vec4 objectDebugColourRGBA;
	bool bUseObjectDebugColour;

	bool bDontLight;

	bool render;

	bool bIsWireframe;

	bool bDisableDepthBufferCheck;

	glm::vec4 wholeObjectDiffuseRGBA;		// The "colour" of the object
	bool bUseWholeObjectDiffuseColour;		// If true, then wholeObject colour (not model vertex) is used

	glm::vec3 wholeObjectSpecularRGB;		// Specular HIGHLIGHT colour (usually the same as the light, or white)
	float wholeObjectShininess_SpecPower;	// 1.0 to ??

	float alphaTransparency;

	//// If you only have 1 texture per object...
	//std::string textureName;
	//// OR...
	//// Your object can have how every many textures you want...
	//std::vector< std::string > vecTextures;
	static const unsigned int MAX_TEXTURES = 8;
	std::string textureNames[MAX_TEXTURES];
	float textureRatios[MAX_TEXTURES];

	void clearTextureRatiosToZero(void);
};
