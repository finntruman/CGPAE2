#pragma once
#include "Collision.h"

static enum COLLECTIBLES
{
	CLTBL_HEALTH, CLTBL_AMMO, CLTBL_SIZE
};

class Collectible :	public Collision
{
private:
	int m_typeIndex;
	std::string m_type[CLTBL_SIZE];

public:
	Collectible(SDL_Renderer &renderer, Level &levelLayout, Vector position, int type);
	~Collectible();
	
	void Update();
	std::string ReturnType() { return m_type[m_typeIndex]; }
};