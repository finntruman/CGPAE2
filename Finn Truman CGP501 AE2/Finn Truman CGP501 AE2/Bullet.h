#pragma once
#include "Collision.h"

class Level;

class Bullet : public Collision
{
private:
	int m_speed;

public:
	Bullet(SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int speed);
	Bullet(SDL_Renderer &renderer, Level &levelLayout, Vector position, int speed);
	~Bullet();
	void Update();
};

