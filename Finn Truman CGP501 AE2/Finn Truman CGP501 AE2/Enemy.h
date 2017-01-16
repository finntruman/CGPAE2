#pragma once
#include "AI.h"

class Enemy : public AI
{
protected:
	int m_points;

public:
	Enemy(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int points, int health);
	~Enemy();
	void Update();
};