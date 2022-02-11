#include "LightManager.h"

#include "GLCommon.h"

#include <sstream>
#include <string>

cLightManager::cLightManager()
{
	// Set all the values of the lights, etc.



}

// This got moved into here (seemed more clear)
/*static*/
cLightHelper cLightManager::lightHelper;


sLight::sLight()
{
	// Clear all the values to the unknown ones
	this->position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	// White light
	this->diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	// White specular highlight
	this->specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	// x = constant, y = linear, z = quadratic, w = DistanceCutOff
	this->atten = glm::vec4(0.0f, 0.1f, 0.01f, 100000.0f);

	this->direction = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f);

	// x = lightType, y = inner angle, z = outer angle, w = TBD
	// 0 = pointlight
	// 1 = spot light
	// 2 = directional light
	this->param1.x = 0;	// Spot light
	this->param1.y = 0.0f;
	this->param1.z = 0.0f;
	this->param1.w = 1.0f;	// not used, so set to 1.0f

	// x = 0 for off, 1 for on
	this->param2 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	// Here's the uniform locations of the light values in the shader
	// Settting these to -1 which is the "not found" or unknown uniform location
	this->position_uniform_location = -1;
	this->diffuse_uniform_location = -1;
	this->specular_uniform_location = -1;
	this->atten_uniform_location = -1;
	this->direction_uniform_location = -1;
	this->param1_uniform_location = -1;
	this->param2_uniform_location = -1;
}



void cLightManager::TurnOnLight(unsigned int lightNumber)
{
	if (lightNumber < cLightManager::NUMBER_OF_LIGHTS)
	{
		this->theLights[lightNumber].param2.x = 1.0f;
	}
	return;
}

void cLightManager::TurnOffLight(unsigned int lightNumber)
{
	if (lightNumber < cLightManager::NUMBER_OF_LIGHTS)
	{
		this->theLights[lightNumber].param2.x = 0.0f;
	}
	return;
}


// This sets up the initial uniform locations from the shader
void cLightManager::SetUpUniformLocations(unsigned int shaderProgram)
{
	// GLint theLights_00_position = glGetUniformLocation(program, "theLights[0].position"); // vec4

//	struct sLight
//	{
//		vec4 position;
//		vec4 diffuse;
//		vec4 specular;	// rgb = highlight colour, w = power
//		vec4 atten;		// x = constant, y = linear, z = quadratic, w = DistanceCutOff
//		vec4 direction;	// Spot, directional lights
//		vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
//						// 0 = pointlight
//						// 1 = spot light
//						// 2 = directional light
//		vec4 param2;	// x = 0 for off, 1 for on
//	};
//	uniform sLight theLights[NUMBEROFLIGHTS];  	// 80 uniforms

	this->theLights[0].position_uniform_location =
		glGetUniformLocation(shaderProgram, "theLights[0].position");

	this->theLights[0].diffuse_uniform_location =
		glGetUniformLocation(shaderProgram, "theLights[0].diffuse");

	this->theLights[0].specular_uniform_location =
		glGetUniformLocation(shaderProgram, "theLights[0].specular");

	this->theLights[0].atten_uniform_location =
		glGetUniformLocation(shaderProgram, "theLights[0].atten");

	this->theLights[0].direction_uniform_location =
		glGetUniformLocation(shaderProgram, "theLights[0].direction");

	this->theLights[0].param1_uniform_location =
		glGetUniformLocation(shaderProgram, "theLights[0].param1");

	this->theLights[0].param2_uniform_location =
		glGetUniformLocation(shaderProgram, "theLights[0].param2");

	// And so on for the rest of the lights...
	this->theLights[9].position_uniform_location =
		glGetUniformLocation(shaderProgram, "theLights[9].position");


	for (unsigned int lightIndex = 0; lightIndex != NUMBER_OF_LIGHTS; lightIndex++)
	{
		std::stringstream ssLight;
		ssLight << "theLights[" << lightIndex << "].";

		this->theLights[lightIndex].position_uniform_location = glGetUniformLocation(shaderProgram, (ssLight.str() + "position").c_str());

		this->theLights[lightIndex].diffuse_uniform_location = glGetUniformLocation(shaderProgram, (ssLight.str() + "diffuse").c_str());

		this->theLights[lightIndex].specular_uniform_location = glGetUniformLocation(shaderProgram, (ssLight.str() + "specular").c_str());

		this->theLights[lightIndex].atten_uniform_location = glGetUniformLocation(shaderProgram, (ssLight.str() + "atten").c_str());

		this->theLights[lightIndex].direction_uniform_location = glGetUniformLocation(shaderProgram, (ssLight.str() + "direction").c_str());

		this->theLights[lightIndex].param1_uniform_location = glGetUniformLocation(shaderProgram, (ssLight.str() + "param1").c_str());

		this->theLights[lightIndex].param2_uniform_location = glGetUniformLocation(shaderProgram, (ssLight.str() + "param2").c_str());

	}//for (unsigned int lightIndex

	return;
}

// Copies the values from the array into the shader
void cLightManager::CopyLightInfoToShader(void)
{
	glUniform4f(this->theLights[0].position_uniform_location,
		this->theLights[0].position.x,
		this->theLights[0].position.y,
		this->theLights[0].position.z,
		this->theLights[0].position.w);

	glUniform4f(this->theLights[0].diffuse_uniform_location,
		this->theLights[0].diffuse.x,
		this->theLights[0].diffuse.y,
		this->theLights[0].diffuse.z,
		this->theLights[0].diffuse.w);

	glUniform4f(this->theLights[0].specular_uniform_location,
		this->theLights[0].specular.x,
		this->theLights[0].specular.y,
		this->theLights[0].specular.z,
		this->theLights[0].specular.w);

	glUniform4f(this->theLights[0].atten_uniform_location,
		this->theLights[0].atten.x,
		this->theLights[0].atten.y,
		this->theLights[0].atten.z,
		this->theLights[0].atten.w);

	glUniform4f(this->theLights[0].direction_uniform_location,
		this->theLights[0].direction.x,
		this->theLights[0].direction.y,
		this->theLights[0].direction.z,
		this->theLights[0].direction.w);

	glUniform4f(this->theLights[0].param1_uniform_location,
		this->theLights[0].param1.x,
		this->theLights[0].param1.y,
		this->theLights[0].param1.z,
		this->theLights[0].param1.w);

	glUniform4f(this->theLights[0].param2_uniform_location,
		this->theLights[0].param2.x,
		this->theLights[0].param2.y,
		this->theLights[0].param2.z,
		this->theLights[0].param2.w);

	// And so on...

	glUniform4f(this->theLights[1].position_uniform_location,
		this->theLights[1].position.x,
		this->theLights[1].position.y,
		this->theLights[1].position.z,
		this->theLights[1].position.w);

	glUniform4f(this->theLights[1].diffuse_uniform_location,
		this->theLights[1].diffuse.x,
		this->theLights[1].diffuse.y,
		this->theLights[1].diffuse.z,
		this->theLights[1].diffuse.w);

	glUniform4f(this->theLights[1].specular_uniform_location,
		this->theLights[1].specular.x,
		this->theLights[1].specular.y,
		this->theLights[1].specular.z,
		this->theLights[1].specular.w);

	glUniform4f(this->theLights[1].atten_uniform_location,
		this->theLights[1].atten.x,
		this->theLights[1].atten.y,
		this->theLights[1].atten.z,
		this->theLights[1].atten.w);

	glUniform4f(this->theLights[1].direction_uniform_location,
		this->theLights[1].direction.x,
		this->theLights[1].direction.y,
		this->theLights[1].direction.z,
		this->theLights[1].direction.w);

	glUniform4f(this->theLights[1].param1_uniform_location,
		this->theLights[1].param1.x,
		this->theLights[1].param1.y,
		this->theLights[1].param1.z,
		this->theLights[1].param1.w);

	glUniform4f(this->theLights[1].param2_uniform_location,
		this->theLights[1].param2.x,
		this->theLights[1].param2.y,
		this->theLights[1].param2.z,
		this->theLights[1].param2.w);

	//
	glUniform4f(this->theLights[2].position_uniform_location,
		this->theLights[2].position.x,
		this->theLights[2].position.y,
		this->theLights[2].position.z,
		this->theLights[2].position.w);

	glUniform4f(this->theLights[2].diffuse_uniform_location,
		this->theLights[2].diffuse.x,
		this->theLights[2].diffuse.y,
		this->theLights[2].diffuse.z,
		this->theLights[2].diffuse.w);

	glUniform4f(this->theLights[2].specular_uniform_location,
		this->theLights[2].specular.x,
		this->theLights[2].specular.y,
		this->theLights[2].specular.z,
		this->theLights[2].specular.w);

	glUniform4f(this->theLights[2].atten_uniform_location,
		this->theLights[2].atten.x,
		this->theLights[2].atten.y,
		this->theLights[2].atten.z,
		this->theLights[2].atten.w);

	glUniform4f(this->theLights[2].direction_uniform_location,
		this->theLights[2].direction.x,
		this->theLights[2].direction.y,
		this->theLights[2].direction.z,
		this->theLights[2].direction.w);

	glUniform4f(this->theLights[2].param1_uniform_location,
		this->theLights[2].param1.x,
		this->theLights[2].param1.y,
		this->theLights[2].param1.z,
		this->theLights[2].param1.w);

	glUniform4f(this->theLights[2].param2_uniform_location,
		this->theLights[2].param2.x,
		this->theLights[2].param2.y,
		this->theLights[2].param2.z,
		this->theLights[2].param2.w);

	glUniform4f(this->theLights[3].position_uniform_location,
		this->theLights[3].position.x,
		this->theLights[3].position.y,
		this->theLights[3].position.z,
		this->theLights[3].position.w);

	glUniform4f(this->theLights[3].diffuse_uniform_location,
		this->theLights[3].diffuse.x,
		this->theLights[3].diffuse.y,
		this->theLights[3].diffuse.z,
		this->theLights[3].diffuse.w);

	glUniform4f(this->theLights[3].specular_uniform_location,
		this->theLights[3].specular.x,
		this->theLights[3].specular.y,
		this->theLights[3].specular.z,
		this->theLights[3].specular.w);

	glUniform4f(this->theLights[3].atten_uniform_location,
		this->theLights[3].atten.x,
		this->theLights[3].atten.y,
		this->theLights[3].atten.z,
		this->theLights[3].atten.w);

	glUniform4f(this->theLights[3].direction_uniform_location,
		this->theLights[3].direction.x,
		this->theLights[3].direction.y,
		this->theLights[3].direction.z,
		this->theLights[3].direction.w);

	glUniform4f(this->theLights[3].param1_uniform_location,
		this->theLights[3].param1.x,
		this->theLights[3].param1.y,
		this->theLights[3].param1.z,
		this->theLights[3].param1.w);

	glUniform4f(this->theLights[3].param2_uniform_location,
		this->theLights[3].param2.x,
		this->theLights[3].param2.y,
		this->theLights[3].param2.z,
		this->theLights[3].param2.w);

	glUniform4f(this->theLights[4].position_uniform_location,
		this->theLights[4].position.x,
		this->theLights[4].position.y,
		this->theLights[4].position.z,
		this->theLights[4].position.w);

	glUniform4f(this->theLights[4].diffuse_uniform_location,
		this->theLights[4].diffuse.x,
		this->theLights[4].diffuse.y,
		this->theLights[4].diffuse.z,
		this->theLights[4].diffuse.w);

	glUniform4f(this->theLights[4].specular_uniform_location,
		this->theLights[4].specular.x,
		this->theLights[4].specular.y,
		this->theLights[4].specular.z,
		this->theLights[4].specular.w);

	glUniform4f(this->theLights[4].atten_uniform_location,
		this->theLights[4].atten.x,
		this->theLights[4].atten.y,
		this->theLights[4].atten.z,
		this->theLights[4].atten.w);

	glUniform4f(this->theLights[4].direction_uniform_location,
		this->theLights[4].direction.x,
		this->theLights[4].direction.y,
		this->theLights[4].direction.z,
		this->theLights[4].direction.w);

	glUniform4f(this->theLights[4].param1_uniform_location,
		this->theLights[4].param1.x,
		this->theLights[4].param1.y,
		this->theLights[4].param1.z,
		this->theLights[4].param1.w);

	glUniform4f(this->theLights[4].param2_uniform_location,
		this->theLights[4].param2.x,
		this->theLights[4].param2.y,
		this->theLights[4].param2.z,
		this->theLights[4].param2.w);

	glUniform4f(this->theLights[5].position_uniform_location,
		this->theLights[5].position.x,
		this->theLights[5].position.y,
		this->theLights[5].position.z,
		this->theLights[5].position.w);

	glUniform4f(this->theLights[5].diffuse_uniform_location,
		this->theLights[5].diffuse.x,
		this->theLights[5].diffuse.y,
		this->theLights[5].diffuse.z,
		this->theLights[5].diffuse.w);

	glUniform4f(this->theLights[5].specular_uniform_location,
		this->theLights[5].specular.x,
		this->theLights[5].specular.y,
		this->theLights[5].specular.z,
		this->theLights[5].specular.w);

	glUniform4f(this->theLights[5].atten_uniform_location,
		this->theLights[5].atten.x,
		this->theLights[5].atten.y,
		this->theLights[5].atten.z,
		this->theLights[5].atten.w);

	glUniform4f(this->theLights[5].direction_uniform_location,
		this->theLights[5].direction.x,
		this->theLights[5].direction.y,
		this->theLights[5].direction.z,
		this->theLights[5].direction.w);

	glUniform4f(this->theLights[5].param1_uniform_location,
		this->theLights[5].param1.x,
		this->theLights[5].param1.y,
		this->theLights[5].param1.z,
		this->theLights[5].param1.w);

	glUniform4f(this->theLights[5].param2_uniform_location,
		this->theLights[5].param2.x,
		this->theLights[5].param2.y,
		this->theLights[5].param2.z,
		this->theLights[5].param2.w);

	return;
}
