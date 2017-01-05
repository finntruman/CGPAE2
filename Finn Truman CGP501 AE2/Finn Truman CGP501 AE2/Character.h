#pragma once
#include "Actor.h"
#include "Bullet.h"
#include <vector>

/*
	A Character is a type of Actor that has lots of additional members and methods to make them seem like physical people within the game, such as the Player and all Enemies
*/

class Character : public Actor
{
private:
	SDL_Renderer* p_renderer; //the Character needs a pointer ot the Renderer for the Bullet's constructor

	void ApplyMovement(); //Once a Character has modified and figured out how much its going to move by this frame (hspeed and vspeed), this function actually applies those movement differences to its position vector

protected:
	//members
	int m_ammo, m_health, m_terminalVelocity;
	float m_hspeed, m_vspeed, m_moveSpeed, m_jumpSpeed, m_gravity;
	bool m_grounded;
	//std::vector<Bullet*> m_bullets;

	//methods
	void Update();
	bool Jump();
	bool Shoot();

public:
	Character(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int health);
	~Character();

	void SetAmmo(int ammo) { m_ammo = ammo; }
	void SetHealth(int health) { m_health = health; }
	void SetSpeed(int speed) { m_moveSpeed = speed; }
	int GetAmmo() { return m_ammo; }
	int GetHealth() { return m_health; }
};

