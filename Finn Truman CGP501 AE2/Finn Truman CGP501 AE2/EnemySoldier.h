#pragma once
#include "Enemy.h"

class EnemySoldier : public Enemy
{
private:
	float m_playerToleranceRange;

	void CheckState();
	void State_Wandering();
	void State_Hostile();

public:
	EnemySoldier(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int points, int health, float toleranceRange = 50.0f);
	~EnemySoldier();

	void Update();
};

