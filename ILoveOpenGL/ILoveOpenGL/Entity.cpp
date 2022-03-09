#include "Entity.h";

Entity::Entity(cMesh* mesh) {
	executing = false;
	this->mesh = mesh;

	facing = FACING_DOWN;
}

Entity::~Entity() {
	delete mesh;
}

void Entity::RegisterParallel(Command cmd) {
	parallels.push(cmd);
}

void Entity::RegisterSerial(Command cmd) {
	if (!executing) {
		serials.push_back(cmd);
	}
}


void Entity::Process() {
	if (executing) {
		if (dispatch == "parallel") {
			switch (parallels.front().type)
			{
			case CMD_MOVE_DIST:
				MoveDistance(parallels.front());
				break;
			case CMD_MOVE_TIME:
				MoveOverTime(parallels.front());
				break;
			case CMD_ORIENT_RADS:
				OrientRadians(parallels.front());
				break;
			case CMD_ORIENT_TIME:
				OrientOverTime(parallels.front());
				break;
			case CMD_FOLLOW:
				Follow(parallels.front());
				break;
			case CMD_FOLLOW_TIME:
				FollowOverTime(parallels.front());
				break;
			case CMD_TRIGGER:
				Trigger(parallels.front());
				break;
			default:
				break;
			}
			if (parallels.front().executed) {
				parallels.pop(); //remove it, since it's done
				executing = false;
				ExecNextParallel();
			}
		}
		else if (dispatch == "serial") {
			executing = false; // assume all are done by default
			for (int i = 0; i < serials.size(); i++) {
				if (!serials[i].executed) {
					switch (serials[i].type)
					{
					case CMD_MOVE_DIST:
						executing |= MoveDistance(serials[i]);
						break;
					case CMD_MOVE_TIME:
						executing |= MoveOverTime(serials[i]);
						break;
					case CMD_ORIENT_RADS:
						executing |= OrientRadians(serials[i]);
						break;
					case CMD_ORIENT_TIME:
						executing |= OrientOverTime(serials[i]);
						break;
					case CMD_FOLLOW:
						executing |= Follow(serials[i]);
						break;
					case CMD_FOLLOW_TIME:
						executing |= FollowOverTime(serials[i]);
						break;
					case CMD_TRIGGER:
						executing |= Trigger(serials[i]);
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void Entity::ExecNextParallel() {
	if (parallels.size() > 0 && !executing) {
		dispatch = "parallel";
		executing = true;
	}
}
void Entity::ExecSerial() {
	if (serials.size() > 0 && !executing) {
		dispatch = "serial";
		executing = true;
	}
}

bool Entity::MoveDistance(Command& cmd) {
	if (cmd.executed) {//this should never happen, but stranger things have happendd
		return false;
	}

	glm::vec3 myPos = mesh->positionXYZ;
	glm::vec3 destinationPos = cmd.target;

	glm::vec3 direction = destinationPos - myPos;

	glm::vec3 normalDir = glm::normalize(direction);

	glm::vec3 velocity = normalDir * cmd.speed * 0.03f;

	//move towards target
	mesh->positionXYZ += velocity;

	float distance = glm::distance(destinationPos, mesh->positionXYZ);
	if (distance > (-0.03f * cmd.speed)&& distance < (0.03f * cmd.speed)) {
		cmd.executed = true;
		return false;
	}

	return true; //must do another pass
}

bool Entity::MoveOverTime(Command& cmd) {
	if (cmd.executed) {//this should never happen, but stranger things have happendd
		return false;
	}

	glm::vec3 myPos = mesh->positionXYZ;
	glm::vec3 destinationPos = cmd.target;

	glm::vec3 direction = destinationPos - myPos;

	glm::vec3 normalDir = glm::normalize(direction);

	float distance = glm::distance(destinationPos, mesh->positionXYZ);

	glm::vec3 velocity = normalDir * (distance/cmd.time) * 0.03f;

	//move towards target
	mesh->positionXYZ += velocity;

	cmd.time -= 0.03f;
	if (cmd.time <= 0) {
		cmd.executed = true;
		return false;
	}

	return true; //must do another pass
}
bool Entity::OrientRadians(Command& cmd) {
	if (cmd.executed) {//this should never happen, but stranger things have happendd
		return false;
	}

	glm::vec3 myPos = mesh->orientationXYZ;
	glm::vec3 destinationPos = cmd.target;

	glm::vec3 direction = destinationPos - myPos;

	glm::vec3 normalDir = glm::normalize(direction);

	glm::vec3 velocity = normalDir * cmd.speed * 0.03f;

	//move towards target
	mesh->orientationXYZ += velocity;

	float distance = glm::distance(destinationPos, mesh->orientationXYZ);
	if (distance > (-0.03f * cmd.speed) && distance < (0.03f * cmd.speed)) {
		cmd.executed = true;
		return false;
	}

	return true; //must do another pass
}
bool Entity::OrientOverTime(Command& cmd) {
	if (cmd.executed) {//this should never happen, but stranger things have happendd
		return false;
	}

	glm::vec3 myPos = mesh->orientationXYZ;
	glm::vec3 destinationPos = cmd.target;

	glm::vec3 direction = destinationPos - myPos;

	glm::vec3 normalDir = glm::normalize(direction);

	float distance = glm::distance(destinationPos, mesh->orientationXYZ);

	glm::vec3 velocity = normalDir * (distance / cmd.time) * 0.03f;

	//move towards target
	mesh->orientationXYZ += velocity;

	cmd.time -= 0.03f;
	if (cmd.time <= 0) {
		cmd.executed = true;
		return false;
	}

	return true; //must do another pass
}

bool Entity::Follow(Command& cmd) {
	if (cmd.executed) {//this should never happen, but stranger things have happendd
		return false;
	}

	glm::vec3 myPos = mesh->positionXYZ;
	glm::vec3 destinationPos = cmd.targetMesh->positionXYZ;

	glm::vec3 direction = destinationPos - myPos;

	glm::vec3 normalDir = glm::normalize(direction);

	glm::vec3 velocity = normalDir * cmd.speed * 0.03f;

	//move towards target
	mesh->positionXYZ += velocity;

	float distance = glm::distance(destinationPos, mesh->positionXYZ);
	if (distance > (-0.03f * cmd.speed) && distance < (0.03f * cmd.speed)) {
		cmd.executed = true;
		return false;
	}

	return true; //must do another pass
}


bool Entity::FollowOverTime(Command& cmd) {
	if (cmd.executed) {//this should never happen, but stranger things have happendd
		return false;
	}

	glm::vec3 myPos = mesh->positionXYZ;
	glm::vec3 destinationPos = cmd.targetMesh->positionXYZ;

	glm::vec3 direction = destinationPos - myPos;

	glm::vec3 normalDir = glm::normalize(direction);

	float distance = glm::distance(destinationPos, mesh->positionXYZ);

	glm::vec3 velocity = normalDir * (distance / cmd.time) * 0.03f;

	//move towards target
	mesh->positionXYZ += velocity;

	cmd.time -= 0.03f;
	if (cmd.time <= 0) {
		cmd.executed = true;
		return false;
	}

	return true; //must do another pass
}

bool Entity::Trigger(Command& cmd) {

	float distance = glm::distance(cmd.target, mesh->positionXYZ);

	if (distance > (-0.03f * cmd.speed) && distance < (0.03f * cmd.speed)) {
		cmd.executed = true;
		return false;
	}

	return false;
}