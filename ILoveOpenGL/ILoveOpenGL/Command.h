#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>

#include "Mesh.h";

enum CommandType {
	CMD_MOVE_DIST = 1,
	CMD_MOVE_TIME = 2,
	CMD_ORIENT_RADS = 3,
	CMD_ORIENT_TIME = 4,
	CMD_FOLLOW = 5,
	CMD_FOLLOW_TIME = 6,
	CMD_TRIGGER = 7
};

struct Command { 
	std::string ref = "default";
	//a reference to the id of the entity meant to exec it
	std::string owner = "";
	int batch = 0;
	//parallel (d) or serial
	std::string dispatch = "parallel";
	//move_dist (d), move_time, orient_rads, orient_time, follow, trigger
	CommandType type = CMD_MOVE_DIST; //make this an enum??
	//the destination
	glm::vec3 target = glm::vec3(0.0f);
	//How fast
	float speed = 0.0f;
	//for how long
	float time = 0.0f;
	//must always be manually set
	cMesh* targetMesh = nullptr;
	//has this finshed executing?
	bool executed = false;
};