#include "Bullet.h"
#include "SDL.h"

Bullet::Bullet(Vector position, std::vector<std::string> sprite, int speed)
	: Collision(position, sprite), m_speed(speed)
{}

Bullet::Bullet(Vector position, int speed)
	: Collision(position, { "assets/bullet.bmp" } ), m_speed(speed)
{}

Bullet::~Bullet()
{}

void Bullet::Update()
{
	if (m_facing == SDL_FLIP_NONE)
	{
		m_position.x += m_speed;
	}
	else m_position.x -= m_speed;

	Collision::Update();
}