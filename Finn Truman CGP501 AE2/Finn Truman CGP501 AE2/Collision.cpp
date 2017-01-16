#include "Collision.h"

Collision::Collision(Vector position, std::vector<std::string> sprite)
	: Actor(position, sprite)
{}

Collision::~Collision()
{}

void Collision::Update()
{
	Actor::Update();
}