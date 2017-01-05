#include "Collision.h"

Collision::Collision(SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite)
	: Actor(nullptr, renderer, levelLayout, position, sprite)
{}

Collision::~Collision()
{}

void Collision::Update()
{
	Actor::Update();
}