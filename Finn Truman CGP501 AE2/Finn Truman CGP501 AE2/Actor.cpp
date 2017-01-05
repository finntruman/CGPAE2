#include "Actor.h"
#include "GameManager.h"
#include "Vector.h"
#include "Sprite.h"
#include "Level.h"

Actor::Actor(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite)
	: p_manager(&manager), m_position(position), p_level(&levelLayout), p_sprite(renderer, *this, sprite), m_facing(SDL_FLIP_NONE)
{}

Actor::Actor(std::nullptr_t nullp, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite)
	: p_manager(nullp), m_position(position), p_level(&levelLayout), p_sprite(renderer, *this, sprite), m_facing(SDL_FLIP_NONE)
{}

Actor::~Actor()
{}

Vector Actor::GetPosition(bool subtractPort)
{
	if (subtractPort) return { m_position.x - p_level->GetViewportPos().x, m_position.y - p_level->GetViewportPos().y };
	else return m_position;
}

void Actor::Update()
{
	p_sprite.DrawSelf();
}

bool Actor::CollisionSprite_Map(float x, float y)
{
	return CollisionSprite_Map({ x, y });
}

bool Actor::CollisionSprite_Map(Vector isCollision)
{
	Vector sprTL(isCollision); //these four vectors create the phantom sprite, which is equal to the collision box of the Character that called this function
	Vector sprTR(isCollision + Vector(p_sprite.GetCollisionWidth() - 1, 0)); //they stand for TopLeft, TopRight, BottomLeft and BottomRight
	Vector sprBL(isCollision + Vector(0, p_sprite.GetCollisionHeight() - 1));
	Vector sprBR(isCollision + Vector(p_sprite.GetCollisionWidth() - 1, p_sprite.GetCollisionHeight() - 1));

	return (p_manager->CollisionPoint_Map(sprTL) || p_manager->CollisionPoint_Map(sprTR) || p_manager->CollisionPoint_Map(sprBL) || p_manager->CollisionPoint_Map(sprBR)); //so if any of these points are colliding, the sprite as a whole is colliding, and returns true
}

int Actor::Sign(float num)
{
	return num / abs(num); //Sign returns either 1, 0 or -1, depending if the parameter is positive, 0, or negative respectively
}