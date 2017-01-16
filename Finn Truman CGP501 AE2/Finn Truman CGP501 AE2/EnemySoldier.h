#pragma once
#include "Enemy.h"

class EnemySoldier : public Enemy
{
private:
	float m_playerToleranceRange;
	int m_reloadTime, m_reloading;

	void CheckState();
	void State_Wandering();
	void State_Hostile();

public:
	EnemySoldier(Vector position, std::vector<std::string> sprite, int points, int health, float toleranceRange = 250.0f);
	~EnemySoldier();

	void Update();
};