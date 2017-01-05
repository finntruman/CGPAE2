#include "Bullet.h"
#include "SDL.h"

Bullet::Bullet(SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int speed)
	: Collision(renderer, levelLayout, position, sprite), m_speed(speed)
{}

Bullet::Bullet(SDL_Renderer &renderer, Level &levelLayout, Vector position, int speed)
	: Collision(renderer, levelLayout, position, { "assets/bullet.bmp" } ), m_speed(speed)
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