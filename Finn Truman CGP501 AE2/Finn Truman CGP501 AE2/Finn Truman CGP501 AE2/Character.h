#pragma once
#include "Actor.h"

/*
	A Character is a type of Actor that has lots of calculations to them to make them seem like physical people within the game, such as the Player and all Enemies
*/

class Character : public Actor
{
private:
	void ApplyMovement(); //Once a Character has modified and figured out how much its going to move by this frame (hspeed and vspeed), this function actually applies those movement differences to its position vector

protected:
	//members
	int m_ammo, m_health, m_terminalVelocity;
	float m_hspeed, m_vspeed, m_moveSpeed, m_jumpSpeed, m_gravity;
	bool m_grounded;

	//methods
	void Update();
	bool Collision(float x, float y); //Collision checks to see if there is a collision at the designated coordinates in WorldSpace, which are turned into LevelSpace in the function
	bool Collision(Vector travel);
	bool SpriteCollision(float x, float y); //SpriteCollision checks to see if the sprite of the Character calling the function would trigger a collision at the designated point in WorldSpace
	bool SpriteCollision(Vector isCollision); //a sprites anchor point is the top left corner
	bool Jump();
	bool Shoot();

	//int Sign(float num);

public:
	Character(SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite);
	~Character();

	void SetAmmo(int ammo) { m_ammo = ammo; }
	void SetHealth(int health) { m_health = health; }
	int GetAmmo() { return m_ammo; }
	int GetHealth() { return m_health; }
};

