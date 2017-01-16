#include "Collectible.h"

Collectible::Collectible(SDL_Renderer &renderer, Level &levelLayout, Vector position, int type)
	: Collision(renderer, levelLayout, position, { " " }), m_typeIndex(type)
{
	m_type[CLTBL_AMMO] = "ammo";
	m_type[CLTBL_HEALTH] = "health";
	p_sprite.ChangeSprite("assets/" + m_type[type] + ".bmp");
}

Collectible::~Collectible()
{
}

void Collectible::Update()
{
	Collision::Update();
}