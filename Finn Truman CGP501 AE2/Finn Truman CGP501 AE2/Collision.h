#pragma once
#include <string>
#include "Actor.h"

class Collision : public Actor
{
private:
	std::string m_type;

public:
	Collision(SDL_Renderer &renderer, Vector position, std::vector<std::string> type); //type is temporarily a vector
	~Collision();
};

