#pragma once

#include "Mesh.h";
#include "Command.h";
#include <vector>
#include <queue>

class Entity {
public:
	bool executing;
	std::string dispatch;
	cMesh* mesh;

	std::queue<Command> parallels;
	std::vector<Command> serials;

	Entity(cMesh* mesh);
	~Entity();

	void RegisterParallel(Command cmd);
	void RegisterSerial(Command cmd);

	//makes sure the currently executing command countinues
	//if no currently executing command, does nothing.
	virtual void Process();

	void ExecNextParallel();
	void ExecSerial();

private:
	bool MoveDistance(Command& cmd);
	bool MoveOverTime(Command& cmd);
	bool OrientRadians(Command& cmd);
	bool OrientOverTime(Command& cmd);
	bool Follow(Command& cmd);
	bool FollowOverTime(Command& cmd);
	bool Trigger(Command& cmd);
};