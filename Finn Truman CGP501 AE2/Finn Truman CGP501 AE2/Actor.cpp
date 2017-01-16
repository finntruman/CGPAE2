#include "Actor.h"
#include "Level.h"
#include "Sprite.h"

Actor::Actor(Vector position, std::vector<std::string> sprite)
	: m_position(position), m_facing(SDL_FLIP_NONE)
{
	m_sprite.Initialise(*this, sprite);
}

Actor::~Actor()
{}

Vector Actor::GetPosition(bool subtractPort)
{
	if (subtractPort) return { m_position.x - p_level->GetViewportPos().x, m_position.y - p_level->GetViewportPos().y };
	else return m_position;
}

void Actor::Update()
{
	m_sprite.DrawSelf();
}