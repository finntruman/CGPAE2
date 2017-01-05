#include "Character.h"
#include "GameManager.h"
#include "Level.h"
#include "Vector.h"

Character::Character(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int health)
	: Actor(manager, renderer, levelLayout, position, sprite), m_ammo(10), m_health(health),
	m_hspeed(0.0f), m_vspeed(0.0f), m_moveSpeed(3.5f), m_jumpSpeed(15.0f), m_gravity(0.8f), m_terminalVelocity(12),	m_grounded(false),
	p_renderer(&renderer)
{
}

Character::~Character()
{
	p_renderer = nullptr;
}

void Character::Update()
{
	ApplyMovement();
	
	//update bullets
	//for (int i = 0; i < m_bullets.size(); i++)
	//{
	//	m_bullets[i]->Update();
	//	if (
	//		CollisionPoint_Map(m_bullets[i]->GetPosition()) //if there is a collision where the bullet is (precise sprite collision is unecesarry)
	//		|| m_bullets[i]->GetPosition().x < 0 //or if the bullet's x is less than 0 (off the left side of the level)
	//		|| m_bullets[i]->GetPosition().x > p_level->LevelSpaceToWorldSpace(p_level->GetWidth(), 0).x //or if the bullet's x is greater than the width of the level
	//		)
	//	{
	//		delete m_bullets[i];
	//		m_bullets.erase(m_bullets.begin() + i); //deleting a pointer's memory still means that that element in the vector is being taken up, it's just empty, so erasing the element reorganises the vector
	//	}
	//}
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
		Bullet* bullet = new Bullet(*p_renderer, *p_level, { m_position.x + p_sprite.GetSpriteWidth() / 2, m_position.y + p_sprite.GetSpriteHeight() / 2 }, 10);
		p_manager->AddBullet(*bullet);
		bullet->SetFlip(m_facing);
		m_ammo--;
		return true;
	}
	else return false;
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