#include "Character.h"
#include "Level.h"
#include "Vector.h"

Character::Character(SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite)
	: Actor(renderer, levelLayout, position, sprite), m_ammo(10), m_health(100),
	m_hspeed(0.0f), m_vspeed(0.0f), m_moveSpeed(3.5f), m_jumpSpeed(15.0f), m_gravity(0.8f), m_terminalVelocity(12),	m_grounded(false)
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
	if (p_level->GetLevelCoord(mapVector) == '.')
	{
		return false; //it was a dot, no collision, return false
	}
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
	Vector sprTL(isCollision); //these four vectors create the phantom sprite, which is equal to the collision box of the Characetr that called this function
	Vector sprTR(isCollision + Vector(p_sprite.GetCollisionWidth() - 1, 0));
	Vector sprBL(isCollision + Vector(0, p_sprite.GetCollisionHeight() - 1));
	Vector sprBR(isCollision + Vector(p_sprite.GetCollisionWidth() - 1, p_sprite.GetCollisionHeight() - 1));

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
	if (!SpriteCollision(m_position.x, m_position.y + 1)) m_grounded = false; //if there IS NOT a wall just below us, set grounded to false
	else m_grounded = true;
		
	if (SpriteCollision(m_position.x, m_position.y + m_vspeed))
	{
		while (!SpriteCollision(m_position.x, m_position.y + Sign(m_vspeed))) //while there isn't a wall 1 pixel in the direction we are travelling...
		{
			m_position.y += 0.1f * Sign(m_vspeed); //move closer to it. this ensures we can get as close to the wall as possible
		}
		m_vspeed = 0;
	}

	if (!m_grounded && m_vspeed < m_terminalVelocity)
	{
		m_vspeed += m_gravity; //add gravity to vspeed if vspeed is below terminal velocity
	}

	m_position.y += m_vspeed; //add the speed
}

int Character::Sign(float num)
{
	return num / abs(num); //Sign returns either -1, 0 or 1, depending if the parameter is positive, negative, or 0
}