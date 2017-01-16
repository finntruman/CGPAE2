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

class GameManager;
class Level;

class Actor
{
protected:
	GameManager* p_manager;
	Level* p_level; //Characters need to be able to see the Level to know if they're going to be colliding with walls. The vector inside the level that actually has all of the level data is private, so all a Character can do is read it
	Vector m_position;
	Sprite p_sprite; //I accidentally named the sprite p_sprite instead of m_sprite, but by the time I realised, it was too late, I had used the wrong name too many times
	SDL_RendererFlip m_facing; //m_facing is a variable that keeps track of which direction an actor is looking. this is needed for when a bullet is created, as it will be identical to the facing member of the actor that spawned it

	//methods
	bool CollisionSprite_Map(float x, float y); //This checks to see if the sprite of the Actor calling the function would trigger a collision with the map at the designated point in WorldSpace
	bool CollisionSprite_Map(Vector isCollision); //a sprites anchor point is the top left corner
	int Sign(float num);

	void Update();

public:
	Actor(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite);
	Actor(std::nullptr_t nullp, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite); //overloaded constructor for Collision subclass, which doesn't need a reference to the manager
	~Actor();

	Vector GetPosition(bool subtractPort = false);
	void SetFlip(SDL_RendererFlip face) { m_facing = face; }
	SDL_RendererFlip GetFlip() { return m_facing; }
	Sprite* GetSprite() { return &p_sprite; }
};