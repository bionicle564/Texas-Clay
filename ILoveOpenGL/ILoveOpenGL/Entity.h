#pragma once

#include "Mesh.h";



enum Facing {
	FACING_UP, //away from cam
	FACING_DOWN, // towards cam
	FACING_LEFT,
	FACING_RIGHT,
};

class Entity {
public:
	bool executing;
	std::string dispatch;

	Facing facing;

	cMesh* mesh;


	Entity(cMesh* mesh);
	~Entity();


	//makes sure the currently executing command countinues
	//if no currently executing command, does nothing.
	virtual void Process(float deltaTime);

private:
	
};