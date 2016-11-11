#pragma once
#include <string>
#include <vector>
#include "SDL.h"
#include "Vector.h"
#include "Sprite.h"

/*
	The Actor class is the base class for just about everything that makes a physical appearence in the game.
	The Actor class has a position vector and a sprite
*/

class Level;

class Actor
{
protected:
	Level* p_level; //Characters need to be able to see the Level to know if they're going to be colliding with walls. The vector inside the level that actually has all of the level data is private, so all a Character can do is read it
	Vector m_position;
	Sprite p_sprite;

	//methods
	void Update();

public:
	Actor(SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite);
	~Actor();

	Vector GetPosition(bool subtractPort = false);
};