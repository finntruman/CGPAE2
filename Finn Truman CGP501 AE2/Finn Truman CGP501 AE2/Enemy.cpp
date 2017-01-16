#include "Enemy.h"

Enemy::Enemy(Vector position, std::vector<std::string> sprite, int points, int health)
	: AI(position, sprite, health), m_points(points)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	AI::Update();
}