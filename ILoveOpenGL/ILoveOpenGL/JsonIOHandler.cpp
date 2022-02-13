#include "JsonIOHandler.h"

JsonIOHandler::JsonIOHandler() {

}

bool JsonIOHandler::WriteSingleModel(const std::string& filePath, cMesh& mesh) {
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "wb"); // non-Windows use "w"

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(os);

	//do actually stuff
	writer.StartObject();
	writer.Key("name");
	writer.String(mesh.nameID.c_str());
	writer.Key("mesh");
	writer.String(mesh.meshName.c_str());
	writer.Key("posx");
	writer.Double(mesh.positionXYZ.x);
	writer.Key("posy");
	writer.Double(mesh.positionXYZ.y);
	writer.Key("posz");
	writer.Double(mesh.positionXYZ.z);
	writer.Key("orix");
	writer.Double(mesh.orientationXYZ.x);
	writer.Key("oriy");
	writer.Double(mesh.orientationXYZ.y);
	writer.Key("oriz");
	writer.Double(mesh.orientationXYZ.z);
	writer.Key("scal");
	writer.Double(mesh.scale);
	writer.Key("litf");
	writer.Bool(mesh.bDontLight);
	writer.Key("depf");
	writer.Bool(mesh.bDisableDepthBufferCheck);
	writer.Key("diff");
	writer.Bool(mesh.bUseWholeObjectDiffuseColour);
	writer.Key("difr");
	writer.Double(mesh.wholeObjectDiffuseRGBA.x);
	writer.Key("difg");
	writer.Double(mesh.wholeObjectDiffuseRGBA.y);
	writer.Key("difb");
	writer.Double(mesh.wholeObjectDiffuseRGBA.z);
	writer.Key("difa");
	writer.Double(mesh.wholeObjectDiffuseRGBA.w);
	writer.Key("spcr");
	writer.Double(mesh.wholeObjectSpecularRGB.x);
	writer.Key("spcg");
	writer.Double(mesh.wholeObjectSpecularRGB.y);
	writer.Key("spcb");
	writer.Double(mesh.wholeObjectSpecularRGB.z);
	writer.Key("spcp");
	writer.Double(mesh.wholeObjectShininess_SpecPower);
	writer.Key("text");
	writer.String(mesh.textureNames[0].c_str());
	writer.EndObject();

	fclose(fp);
	return true;
}

bool JsonIOHandler::ReadSingleModel(const std::string& filePath, cMesh& mesh) {
	//Open the file
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb"); // non-Windows use "r"

	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document d;
	d.ParseStream(is);

	//do actual stuff
	//do actual stuff
	mesh.meshName = d["name"].GetString();
	mesh.meshName = d["mesh"].GetString();
	mesh.positionXYZ.x = d["posx"].GetFloat();
	mesh.positionXYZ.y = d["posy"].GetFloat();
	mesh.positionXYZ.z = d["posz"].GetFloat();
	mesh.orientationXYZ.x = d["orix"].GetFloat();
	mesh.orientationXYZ.y = d["oriy"].GetFloat();
	mesh.orientationXYZ.z = d["oriz"].GetFloat();
	mesh.scale = d["scal"].GetFloat();
	mesh.bDontLight = d["litf"].GetBool();
	mesh.bDisableDepthBufferCheck = d["depf"].GetBool();
	mesh.bUseWholeObjectDiffuseColour = d["diff"].GetBool();
	mesh.wholeObjectDiffuseRGBA.x = d["difr"].GetFloat();
	mesh.wholeObjectDiffuseRGBA.y = d["difg"].GetFloat();
	mesh.wholeObjectDiffuseRGBA.z = d["difb"].GetFloat();
	mesh.wholeObjectDiffuseRGBA.w = d["difa"].GetFloat();
	mesh.wholeObjectSpecularRGB.x = d["spcr"].GetFloat();
	mesh.wholeObjectSpecularRGB.y = d["spcg"].GetFloat();
	mesh.wholeObjectSpecularRGB.z = d["spcb"].GetFloat();
	mesh.wholeObjectShininess_SpecPower = d["spcp"].GetFloat();
	mesh.textureNames[0] = d["text"].GetString();
	mesh.textureRatios[0] = 1.0f;

	fclose(fp);
	return true;
}


bool JsonIOHandler::WriteSingleLight(const std::string& filePath, sLight& light) {
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "wb"); // non-Windows use "w"

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(os);

	//do actually stuff
	writer.StartObject();
	writer.Key("posx");
	writer.Double(light.position.x);
	writer.Key("posy");
	writer.Double(light.position.y);
	writer.Key("posz");
	writer.Double(light.position.z);
	writer.Key("posw");
	writer.Double(light.position.w);
	writer.Key("difr");
	writer.Double(light.diffuse.x);
	writer.Key("difg");
	writer.Double(light.diffuse.y);
	writer.Key("difb");
	writer.Double(light.diffuse.z);
	writer.Key("difa");
	writer.Double(light.diffuse.w);
	writer.Key("spcr");
	writer.Double(light.specular.x);
	writer.Key("spcg");
	writer.Double(light.specular.y);
	writer.Key("spcb");
	writer.Double(light.specular.z);
	writer.Key("spcp");
	writer.Double(light.specular.w);
	writer.Key("atnc");
	writer.Double(light.atten.x);
	writer.Key("atnl");
	writer.Double(light.atten.y);
	writer.Key("atnq");
	writer.Double(light.atten.z);
	writer.Key("atnd");
	writer.Double(light.atten.w);
	writer.Key("dirx");
	writer.Double(light.direction.x);
	writer.Key("diry");
	writer.Double(light.direction.y);
	writer.Key("dirz");
	writer.Double(light.direction.z);
	writer.Key("dirw");
	writer.Double(light.direction.w);
	writer.Key("type");
	writer.Double(light.param1.x);
	writer.Key("iang");
	writer.Double(light.param1.y);
	writer.Key("oang");
	writer.Double(light.param1.z);
	writer.Key("ison");
	writer.Double(light.param2.x);
	writer.EndObject();

	fclose(fp);
	return true;
}

bool JsonIOHandler::ReadSingleLight(const std::string& filePath, sLight& light) {
	//Open the file
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb"); // non-Windows use "r"

	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document d;
	d.ParseStream(is);

	//do actual stuff
	light.position.x = d["posx"].GetFloat();
	light.position.y = d["posy"].GetFloat();
	light.position.z = d["posz"].GetFloat();
	light.position.w = d["posw"].GetFloat();
	light.diffuse.x = d["difr"].GetFloat();
	light.diffuse.y = d["difg"].GetFloat();
	light.diffuse.z = d["difb"].GetFloat();
	light.diffuse.w = d["difa"].GetFloat();
	light.specular.x = d["spcr"].GetFloat();
	light.specular.y = d["spcg"].GetFloat();
	light.specular.z = d["spcb"].GetFloat();
	light.specular.w = d["spcp"].GetFloat();
	light.atten.x = d["atnc"].GetFloat();
	light.atten.y = d["atnl"].GetFloat();
	light.atten.z = d["atnq"].GetFloat();
	light.atten.w = d["atnd"].GetFloat();
	light.direction.x = d["dirx"].GetFloat();
	light.direction.y = d["diry"].GetFloat();
	light.direction.z = d["dirz"].GetFloat();
	light.direction.w = d["dirw"].GetFloat();
	light.param1.x = d["type"].GetFloat();
	light.param1.y = d["iang"].GetFloat();
	light.param1.z = d["oang"].GetFloat();
	light.param2.x = d["ison"].GetFloat();

	fclose(fp);
	return true;
}


bool JsonIOHandler::WriteManyModels(const std::string& filePath, std::vector<Entity*>& entities) {
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "wb"); // non-Windows use "w"

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(os);

	//do actually stuff
	writer.StartObject();
	writer.Key("scene");
	writer.StartArray();
	for (int i = 0; i < entities.size(); i++) {
		writer.StartObject();
		writer.Key("name");
		writer.String(entities[i]->mesh->nameID.c_str());
		writer.Key("mesh");
		writer.String(entities[i]->mesh->meshName.c_str());
		writer.Key("posx");
		writer.Double(entities[i]->mesh->positionXYZ.x);
		writer.Key("posy");
		writer.Double(entities[i]->mesh->positionXYZ.y);
		writer.Key("posz");
		writer.Double(entities[i]->mesh->positionXYZ.z);
		writer.Key("orix");
		writer.Double(entities[i]->mesh->orientationXYZ.x);
		writer.Key("oriy");
		writer.Double(entities[i]->mesh->orientationXYZ.y);
		writer.Key("oriz");
		writer.Double(entities[i]->mesh->orientationXYZ.z);
		writer.Key("scal");
		writer.Double(entities[i]->mesh->scale);
		writer.Key("litf");
		writer.Bool(entities[i]->mesh->bDontLight);
		writer.Key("depf");
		writer.Bool(entities[i]->mesh->bDisableDepthBufferCheck);
		writer.Key("diff");
		writer.Bool(entities[i]->mesh->bUseWholeObjectDiffuseColour);
		writer.Key("difr");
		writer.Double(entities[i]->mesh->wholeObjectDiffuseRGBA.x);
		writer.Key("difg");
		writer.Double(entities[i]->mesh->wholeObjectDiffuseRGBA.y);
		writer.Key("difb");
		writer.Double(entities[i]->mesh->wholeObjectDiffuseRGBA.z);
		writer.Key("difa");
		writer.Double(entities[i]->mesh->wholeObjectDiffuseRGBA.w);
		writer.Key("spcr");
		writer.Double(entities[i]->mesh->wholeObjectSpecularRGB.x);
		writer.Key("spcg");
		writer.Double(entities[i]->mesh->wholeObjectSpecularRGB.y);
		writer.Key("spcb");
		writer.Double(entities[i]->mesh->wholeObjectSpecularRGB.z);
		writer.Key("spcp");
		writer.Double(entities[i]->mesh->wholeObjectShininess_SpecPower);
		writer.Key("text");
		writer.String(entities[i]->mesh->textureNames[0].c_str());
		writer.EndObject();
	}
	writer.EndArray();
	writer.EndObject();

	fclose(fp);
	return true;
}

bool JsonIOHandler::ReadManyModels(const std::string& filePath, std::vector<Entity*>& entities) {
	//Open the file
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb"); // non-Windows use "r"

	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document d;
	d.ParseStream(is);

	//do actual stuff
	for (int i = 0; i < d["scene"].GetArray().Size(); i++) {
		cMesh* readIn = new cMesh();
		readIn->nameID = d["scene"].GetArray()[i].GetObject()["name"].GetString();
		readIn->meshName = d["scene"].GetArray()[i].GetObject()["mesh"].GetString();
		readIn->positionXYZ.x = d["scene"].GetArray()[i].GetObject()["posx"].GetFloat();
		readIn->positionXYZ.y = d["scene"].GetArray()[i].GetObject()["posy"].GetFloat();
		readIn->positionXYZ.z = d["scene"].GetArray()[i].GetObject()["posz"].GetFloat();
		readIn->orientationXYZ.x = d["scene"].GetArray()[i].GetObject()["orix"].GetFloat();
		readIn->orientationXYZ.y = d["scene"].GetArray()[i].GetObject()["oriy"].GetFloat();
		readIn->orientationXYZ.z = d["scene"].GetArray()[i].GetObject()["oriz"].GetFloat();
		readIn->scale = d["scene"].GetArray()[i].GetObject()["scal"].GetFloat();
		readIn->bDontLight = d["scene"].GetArray()[i].GetObject()["litf"].GetBool();
		readIn->bDisableDepthBufferCheck = d["scene"].GetArray()[i].GetObject()["depf"].GetBool();
		readIn->bUseWholeObjectDiffuseColour = d["scene"].GetArray()[i].GetObject()["diff"].GetBool();
		readIn->wholeObjectDiffuseRGBA.x = d["scene"].GetArray()[i].GetObject()["difr"].GetFloat();
		readIn->wholeObjectDiffuseRGBA.y = d["scene"].GetArray()[i].GetObject()["difg"].GetFloat();
		readIn->wholeObjectDiffuseRGBA.z = d["scene"].GetArray()[i].GetObject()["difb"].GetFloat();
		readIn->wholeObjectDiffuseRGBA.w = d["scene"].GetArray()[i].GetObject()["difa"].GetFloat();
		readIn->wholeObjectSpecularRGB.x = d["scene"].GetArray()[i].GetObject()["spcr"].GetFloat();
		readIn->wholeObjectSpecularRGB.y = d["scene"].GetArray()[i].GetObject()["spcg"].GetFloat();
		readIn->wholeObjectSpecularRGB.z = d["scene"].GetArray()[i].GetObject()["spcb"].GetFloat();
		readIn->wholeObjectShininess_SpecPower = d["scene"].GetArray()[i].GetObject()["spcp"].GetFloat();
		readIn->textureNames[0] = d["scene"].GetArray()[i].GetObject()["text"].GetString();
		readIn->textureRatios[0] = 1.0f;
		Entity* ent = new Entity(readIn);
		entities.push_back(ent);
	}

	fclose(fp);
	return true;
}


bool JsonIOHandler::WriteManyLights(const std::string& filePath, std::vector<sLight>& lights) {
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "wb"); // non-Windows use "w"

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(os);

	//do actually stuff
	writer.StartObject();
	writer.Key("scene");
	writer.StartArray();
	for (int i = 0; i < lights.size(); i++) {
		writer.StartObject();
		writer.Key("posx");
		writer.Double(lights[i].position.x);
		writer.Key("posy");
		writer.Double(lights[i].position.y);
		writer.Key("posz");
		writer.Double(lights[i].position.z);
		writer.Key("posw");
		writer.Double(lights[i].position.w);
		writer.Key("difr");
		writer.Double(lights[i].diffuse.x);
		writer.Key("difg");
		writer.Double(lights[i].diffuse.y);
		writer.Key("difb");
		writer.Double(lights[i].diffuse.z);
		writer.Key("difa");
		writer.Double(lights[i].diffuse.w);
		writer.Key("spcr");
		writer.Double(lights[i].specular.x);
		writer.Key("spcg");
		writer.Double(lights[i].specular.y);
		writer.Key("spcb");
		writer.Double(lights[i].specular.z);
		writer.Key("spcp");
		writer.Double(lights[i].specular.w);
		writer.Key("atnc");
		writer.Double(lights[i].atten.x);
		writer.Key("atnl");
		writer.Double(lights[i].atten.y);
		writer.Key("atnq");
		writer.Double(lights[i].atten.z);
		writer.Key("atnd");
		writer.Double(lights[i].atten.w);
		writer.Key("dirx");
		writer.Double(lights[i].direction.x);
		writer.Key("diry");
		writer.Double(lights[i].direction.y);
		writer.Key("dirz");
		writer.Double(lights[i].direction.z);
		writer.Key("dirw");
		writer.Double(lights[i].direction.w);
		writer.Key("type");
		writer.Double(lights[i].param1.x);
		writer.Key("iang");
		writer.Double(lights[i].param1.y);
		writer.Key("oang");
		writer.Double(lights[i].param1.z);
		writer.Key("ison");
		writer.Double(lights[i].param2.x);
		writer.EndObject();
	}
	writer.EndArray();
	writer.EndObject();

	fclose(fp);
	return true;
}

bool JsonIOHandler::ReadManyLights(const std::string& filePath, std::vector<sLight>& lights) {
	//Open the file
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb"); // non-Windows use "r"

	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document d;
	d.ParseStream(is);

	//do actual stuff
	for (int i = 0; i < d["scene"].GetArray().Size(); i++) {
		sLight readIn;
		readIn.position.x = d["scene"].GetArray()[i].GetObject()["posx"].GetFloat();
		readIn.position.y = d["scene"].GetArray()[i].GetObject()["posy"].GetFloat();
		readIn.position.z = d["scene"].GetArray()[i].GetObject()["posz"].GetFloat();
		readIn.position.w = d["scene"].GetArray()[i].GetObject()["posw"].GetFloat();
		readIn.diffuse.x = d["scene"].GetArray()[i].GetObject()["difr"].GetFloat();
		readIn.diffuse.y = d["scene"].GetArray()[i].GetObject()["difg"].GetFloat();
		readIn.diffuse.z = d["scene"].GetArray()[i].GetObject()["difb"].GetFloat();
		readIn.diffuse.w = d["scene"].GetArray()[i].GetObject()["difa"].GetFloat();
		readIn.specular.x = d["scene"].GetArray()[i].GetObject()["spcr"].GetFloat();
		readIn.specular.y = d["scene"].GetArray()[i].GetObject()["spcg"].GetFloat();
		readIn.specular.z = d["scene"].GetArray()[i].GetObject()["spcb"].GetFloat();
		readIn.specular.w = d["scene"].GetArray()[i].GetObject()["spcp"].GetFloat();
		readIn.atten.x = d["scene"].GetArray()[i].GetObject()["atnc"].GetFloat();
		readIn.atten.y = d["scene"].GetArray()[i].GetObject()["atnl"].GetFloat();
		readIn.atten.z = d["scene"].GetArray()[i].GetObject()["atnq"].GetFloat();
		readIn.atten.w = d["scene"].GetArray()[i].GetObject()["atnd"].GetFloat();
		readIn.direction.x = d["scene"].GetArray()[i].GetObject()["dirx"].GetFloat();
		readIn.direction.y = d["scene"].GetArray()[i].GetObject()["diry"].GetFloat();
		readIn.direction.z = d["scene"].GetArray()[i].GetObject()["dirz"].GetFloat();
		readIn.direction.w = d["scene"].GetArray()[i].GetObject()["dirw"].GetFloat();
		readIn.param1.x = d["scene"].GetArray()[i].GetObject()["type"].GetFloat();
		readIn.param1.y = d["scene"].GetArray()[i].GetObject()["iang"].GetFloat();
		readIn.param1.z = d["scene"].GetArray()[i].GetObject()["oang"].GetFloat();
		readIn.param2.x = d["scene"].GetArray()[i].GetObject()["ison"].GetFloat();
		lights.push_back(readIn);
	}

	fclose(fp);
	return true;
}

bool JsonIOHandler::WriteManyAnims(const std::string& filePath, std::vector<Command>& commands) {
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "wb"); // non-Windows use "w"

	char writeBuffer[65536];
	FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));

	Writer<FileWriteStream> writer(os);

	//do actually stuff
	writer.StartObject();
	writer.Key("scene");
	writer.StartArray();
	for (int i = 0; i < commands.size(); i++) {
		writer.StartObject();
		writer.Key("refr");
		writer.String(commands[i].ref.c_str());
		writer.Key("ownr");
		writer.String(commands[i].owner.c_str());
		writer.Key("batc");
		writer.Int(commands[i].batch);
		writer.Key("dspt");
		writer.String(commands[i].dispatch.c_str());
		writer.Key("type");
		writer.Int(commands[i].type);
		writer.Key("tarx");
		writer.Double(commands[i].target.x);
		writer.Key("tary");
		writer.Double(commands[i].target.y);
		writer.Key("tarz");
		writer.Double(commands[i].target.z);
		writer.Key("sped");
		writer.Double(commands[i].speed);
		writer.Key("time");
		writer.Double(commands[i].time);
		writer.EndObject();
	}
	writer.EndArray();
	writer.EndObject();

	fclose(fp);
	return true;
}

bool JsonIOHandler::ReadManyAnims(const std::string& filePath, std::vector<Command>& commands) {
	//Open the file
	using namespace rapidjson;

	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb"); // non-Windows use "r"

	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	Document d;
	d.ParseStream(is);

	//do actual stuff
	for (int i = 0; i < d["scene"].GetArray().Size(); i++) {
		Command holder;

		holder.ref = d["scene"].GetArray()[i].GetObject()["refr"].GetString();
		holder.owner = d["scene"].GetArray()[i].GetObject()["ownr"].GetString();
		holder.batch = d["scene"].GetArray()[i].GetObject()["batc"].GetInt();
		holder.dispatch = d["scene"].GetArray()[i].GetObject()["dspt"].GetString();
		holder.type = (CommandType)d["scene"].GetArray()[i].GetObject()["type"].GetInt();
		holder.target.x = d["scene"].GetArray()[i].GetObject()["tarx"].GetFloat();
		holder.target.y = d["scene"].GetArray()[i].GetObject()["tary"].GetFloat();
		holder.target.z = d["scene"].GetArray()[i].GetObject()["tarz"].GetFloat();
		holder.speed = d["scene"].GetArray()[i].GetObject()["sped"].GetFloat();
		holder.time = d["scene"].GetArray()[i].GetObject()["time"].GetFloat();

		commands.push_back(holder);
	}

	fclose(fp);
	return true;
}