#pragma once

//JsonIOHandler.h
//Gian Tullo, 0886424
//191021
//Reads in and Writes out Praticle Presets

#include <string>
#include <vector>

#include <rapidjson/filereadstream.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include "rapidjson/filewritestream.h"

#include "Entity.h"
#include "Command.h"
#include "LightManager.h"

class JsonIOHandler {
public:
	JsonIOHandler();

	bool WriteSingleModel(const std::string& filePath, cMesh& mesh);
	bool ReadSingleModel(const std::string& filePath, cMesh& mesh);

	bool WriteSingleLight(const std::string& filePath, sLight& light);
	bool ReadSingleLight(const std::string& filePath, sLight& light);

	bool WriteManyModels(const std::string& filePath, std::vector<Entity*>& entities);
	bool ReadManyModels(const std::string& filePath, std::vector<Entity*>& entities);

	bool WriteManyLights(const std::string& filePath, std::vector<sLight>& lights);
	bool ReadManyLights(const std::string& filePath, std::vector<sLight>& lights);

	bool WriteManyAnims(const std::string& filePath, std::vector<Command>& commands);
	bool ReadManyAnims(const std::string& filePath, std::vector<Command>& commands);
};