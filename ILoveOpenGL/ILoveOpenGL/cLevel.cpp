#include "cLevel.h"

cLevel::~cLevel()
{
	for (int i = 0; i < plataforms.size(); i++)
	{
		delete plataforms[i];
	}

	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
}
