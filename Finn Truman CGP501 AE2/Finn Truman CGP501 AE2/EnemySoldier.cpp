#include "EnemySoldier.h"

EnemySoldier::EnemySoldier(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int points, int health, float toleranceRange)
	: Enemy(manager, renderer, levelLayout, position, sprite, points, health), m_playerToleranceRange(toleranceRange)
{
	SetSpeed(2.8f);
}

EnemySoldier::~EnemySoldier()
{
}

void EnemySoldier::Update()
{
	CheckState();
	Enemy::Update();
}

void EnemySoldier::CheckState()
{
	switch (m_stateMachine)
	{
	case STT_WANDERING:
		State_Wandering();
		break;

	case STT_HOSTILE:
		State_Hostile();
		break;
	}
}

void EnemySoldier::State_Wandering()
{
	if (DistanceToPlayer() <= m_playerToleranceRange)
	{
		m_stateMachine = STT_HOSTILE;
	}
}

void EnemySoldier::State_Hostile()
{
	if (DistanceToPlayer() > m_playerToleranceRange)
	{
		m_stateMachine = STT_WANDERING;
	}
}