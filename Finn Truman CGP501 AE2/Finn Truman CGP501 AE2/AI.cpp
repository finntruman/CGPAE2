#include "AI.h"
#include "GameManager.h"
#include <math.h>

AI::AI(Vector position, std::vector<std::string> sprite, int health)
	: Character(position, sprite, health)
{}

AI::~AI()
{}

void AI::Update()
{
	if (CollisionSprite_Map(m_position.x + m_hspeed, m_position.y))
	{
		Jump();
	}
	Character::Update();
}

float AI::DistanceToPlayer()
{
	//pythagoras
	Vector pointA = p_player->GetPosition();
	Vector pointC = GetPosition();
	Vector pointB(pointC.x, pointA.y);

	float AtoB = pointB.x - pointA.x;
	float BtoC = pointC.y - pointB.y;

	//sqrt(A*A + B*B)
	return std::sqrt(AtoB*AtoB + BtoC*BtoC);
}
