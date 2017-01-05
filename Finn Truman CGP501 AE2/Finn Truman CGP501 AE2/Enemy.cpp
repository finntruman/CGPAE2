#include "Enemy.h"

Enemy::Enemy(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int points, int health)
	: AI(manager, renderer, levelLayout, position, sprite, health), m_points(points)
{
}

Enemy::~Enemy()
{
}
