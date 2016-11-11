#include "Character.h"
#include "Level.h"
#include "Vector.h"

Character::Character(SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite)
	: Actor(renderer, levelLayout, position, sprite), m_ammo(10), m_health(100),
	m_hspeed(0.0f), m_vspeed(0.0f), m_moveSpeed(3.5f), m_jumpSpeed(13.0f), m_gravity(0.8f), m_terminalVelocity(12),	m_grounded(false)
{
}

Character::~Character()
{
}

void Character::Update()
{
	ApplyMovement();
	Actor::Update();
}

bool Character::Collision(float x, float y)
{
	Vector mapVector = p_level->WorldSpaceToLevelSpace(x, y);
	if (p_level->GetLevelCoord(mapVector) == '.') return false; //it was a dot, no collision, return false
	else return true; //it was something other than a dot, collision, return true
}

bool Character::Collision(Vector travel)
{
	return Collision(travel.x, travel.y);
}

bool Character::SpriteCollision(float x, float y)
{
	return SpriteCollision({x, y});
}

bool Character::SpriteCollision(Vector isCollision)
{
	Vector sprTL(isCollision); //these four vectors create the phantom sprite, which is equal to the sprite of the Characetr that called this function
	Vector sprTR(isCollision + Vector(p_sprite.GetWidth() - 1, 0));
	Vector sprBL(isCollision + Vector(0, p_sprite.GetHeight() - 1));
	Vector sprBR(isCollision + Vector(p_sprite.GetWidth() - 1, p_sprite.GetHeight() - 1));

	return (Collision(sprTL) || Collision(sprTR) || Collision(sprBL) || Collision(sprBR));
}

bool Character::Jump()
{
	if (m_grounded)
	{
		m_vspeed = -m_jumpSpeed;
		m_grounded = false;
		return true; //sucesfully jumped
	}
	return false; //failed to jump
}

bool Character::Shoot()
{
	return false;
}

void Character::ApplyMovement()
{
	//HORIZONTAL COLLISION
	if (SpriteCollision(m_position.x + m_hspeed, m_position.y)) //if there is a collision where we're about to be...
	{
		m_hspeed = 0;
	}

	m_position.x += m_hspeed; //add the speed
	m_hspeed = 0;
	
	//VERTICAL COLLISION
	if (m_grounded)
	{
		if (!SpriteCollision(m_position.x, m_position.y + 0.1f)) m_grounded = false; //if there IS NOT a wall just below us, set grounded to false
	}
	else if (m_vspeed < m_terminalVelocity)
	{
		m_vspeed += m_gravity; //add gravity to vspeed if vspeed is below terminal velocity
	}

	if (SpriteCollision(m_position.x, m_position.y + m_vspeed))
	{
		m_vspeed = 0;
		m_grounded = true;
	}

	m_position.y += m_vspeed; //add the speed
}

//int Character::Sign(float num)
//{
//	return num / fmax(abs(num), 1);
//}