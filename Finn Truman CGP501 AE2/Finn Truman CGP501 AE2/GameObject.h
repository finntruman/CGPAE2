#pragma once
#include <vector>
#include <string>

#include "SDL.h"
#include "Vector.h"
#include "Sprite.h"

class GameManager;
class Input;
class Level;
class Actor;
class Player;
//class Sprite;

class GameObject
{
protected:
	//MEMBERS
	//pointers
	static SDL_Renderer* p_renderer;
	static GameManager* p_manager;
	static Input* p_input;
	static Level* p_level;
	static Player* p_player;

	//members
	Sprite m_sprite; //the sprite remains dormant until the Actor initialises it

public:
	GameObject();
	~GameObject();

	//#~# METHODS #~#
	int Clamp(int toClamp, int min, int max);
	float DistanceTo(Vector point1, Vector point2);
	int Sign(float num);

	//COLLISION METHODS
	//Collision with the map at the parameter coords in WorldSpace (coords are turned into LevelSpace in the method)
	bool CollisionPoint_Map(float x, float y);
	bool CollisionPoint_Map(Vector point);

	//CollisionSprite_Map checks if the sprite of the actor (default sprite is that of the object that calls it) would trigger a collision with the map at the parameter coords
	bool CollisionSprite_Map(float x, float y);
	bool CollisionSprite_Map(Vector position);
	bool CollisionSprite_Map(GameObject* collision, float x, float y);
	bool CollisionSprite_Map(GameObject* collision, Vector position);

	//Checks to see if the sprite of the class calling the method would trigger a collision with the second parameter
	bool CollisionSprite_Object(Actor* collision1, Actor* collision2);
};

