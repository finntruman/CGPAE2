#include "Character.h"
#include "GameManager.h"
#include "Level.h"
#include "Vector.h"

Character::Character(Vector position, std::vector<std::string> sprite, int health)
	: Actor(position, sprite), m_ammo(10), m_health(health),
	m_hspeed(0.0f), m_vspeed(0.0f), m_moveSpeed(3.5f), m_jumpSpeed(15.0f), m_gravity(0.8f), m_terminalVelocity(12),	m_grounded(false)
{
}

Character::~Character()
{}

void Character::Update()
{
	ApplyMovement();
	Actor::Update();
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
	if (m_ammo > 0)
	{
		int flip = m_facing == SDL_FLIP_HORIZONTAL ? -1 : 1; //this is set to -1 if the sprite is flipped (facing left) or 1 if not flipped (facing right)
		//this is a fix to a bug where a bullet that a character fires will be overlapping themselves, therefor hitting them immediately
		Bullet* bullet = new Bullet({ m_position.x + m_sprite.GetSpriteWidth() * flip, m_position.y + m_sprite.GetSpriteHeight() / 2 }, 10);
		p_manager->AddBullet(*bullet);
		bullet->SetFlip(m_facing);
		m_ammo--;
		return true;
	}
	else return false;
}

Vector Character::MoveTowards(Actor* target, int speed)
{
	Vector targetPos = target->GetPosition();
	Vector returnValue;
	returnValue.x = speed * Sign(targetPos.x - m_position.x); //will return -1, 0 or 1 if the target's x is less than, equal to or greater than our current position, respectively
	returnValue.y = speed * Sign(targetPos.y - m_position.y);
	return returnValue;
}

void Character::ApplyMovement()
{
	//HORIZONTAL COLLISION
	if (CollisionSprite_Map(m_position.x + m_hspeed, m_position.y)) //if there is a collision where we're about to be...
	{
		m_hspeed = 0;
	}

	m_position.x += m_hspeed; //add the speed
	m_hspeed = 0;
	
	//VERTICAL COLLISION
	if (!CollisionSprite_Map(m_position.x, m_position.y + 1)) m_grounded = false; //if there IS NOT a wall just below us, set grounded to false
	else m_grounded = true;
		
	if (CollisionSprite_Map(m_position.x, m_position.y + m_vspeed))
	{
		while (!CollisionSprite_Map(m_position.x, m_position.y + Sign(m_vspeed))) //while there isn't a wall 1 pixel in the direction we are travelling...
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