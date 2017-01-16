#include "Collectible.h"

Collectible::Collectible(Vector position, int type)
	: Collision(position, { " " }), m_typeIndex(type)
{
	m_type[CLTBL_AMMO] = "ammo";
	m_type[CLTBL_HEALTH] = "health";
	m_sprite.ChangeSprite("assets/" + m_type[type] + ".bmp");
}

Collectible::~Collectible()
{
}

void Collectible::Update()
{
	Collision::Update();
}