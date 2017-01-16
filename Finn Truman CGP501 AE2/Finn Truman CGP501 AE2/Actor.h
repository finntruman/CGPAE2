#pragma once
#include "GameObject.h"

/*
	The Actor class is the base class for just about everything that makes a physical appearence in the game.
	The Actor class has a position vector and a sprite
*/

class Actor : public GameObject
{
protected:
	Vector m_position;
	SDL_RendererFlip m_facing; //m_facing is a variable that keeps track of which direction an actor is looking. this is needed for when a bullet is created, as it will be identical to the facing member of the actor that spawned it

	//methods
	void Update();

public:
	Actor(Vector position, std::vector<std::string> sprite);
	~Actor();

	Vector GetPosition(bool subtractPort = false);
	void SetFlip(SDL_RendererFlip face) { m_facing = face; }
	SDL_RendererFlip GetFlip() { return m_facing; }
	Sprite* GetSprite() { return &m_sprite; }
};