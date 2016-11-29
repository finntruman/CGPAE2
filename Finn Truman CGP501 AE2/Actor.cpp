#include "Actor.h"
#include "Vector.h"
#include "Sprite.h"
#include "Level.h"

Actor::Actor(SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite)
	: m_position(position), p_level(&levelLayout), p_sprite(renderer, *this, sprite), m_facing(SDL_FLIP_NONE)
{}

Actor::~Actor()
{}

Vector Actor::GetPosition(bool subtractPort)
{
	if (subtractPort) return{ m_position.x - p_level->GetViewportPos().x, m_position.y - p_level->GetViewportPos().y };
	else return m_position;
}

void Actor::Update()
{
	p_sprite.DrawSelf();
}