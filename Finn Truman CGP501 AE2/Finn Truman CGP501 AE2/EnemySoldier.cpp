#include "EnemySoldier.h"

EnemySoldier::EnemySoldier(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int points, int health, float toleranceRange)
	: Enemy(manager, renderer, levelLayout, position, sprite, points, health), m_playerToleranceRange(toleranceRange)
{
	SetSpeed(2.8f);
	m_playerToleranceRange = 250.0f;
	m_reloadTime = 60;
	m_reloading = 0;
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

	m_hspeed -= MoveTowards(p_player, m_moveSpeed).x;
	if (m_hspeed > 0) m_facing = SDL_FLIP_HORIZONTAL;
	if (m_hspeed < 0) m_facing = SDL_FLIP_NONE;

	if (m_reloading-- != 0);
	else
	{
		Shoot();
		m_reloading = m_reloadTime;
	}
}