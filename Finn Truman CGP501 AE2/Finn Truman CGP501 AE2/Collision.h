#pragma once
#include <string>
#include "Actor.h"

/*
	The Collision class is an entity that exists in World Space that causes something to happen when it collides with something else.
	Collision differs from Character because characters have AI to make them do something, while Collision classes work on basic logic, such as a bullet or collectible
*/

class Collision : public Actor
{
public:
	Collision(Vector position, std::vector<std::string> sprite);
	~Collision();
	void Update();
};