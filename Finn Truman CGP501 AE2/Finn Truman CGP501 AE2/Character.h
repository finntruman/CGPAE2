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
	void ApplyMovement(); //Once a Character has modified and figured out how much its going to move by this frame (hspeed and vspeed), this function actually applies those movement differences to its position vector

protected:
	//members
	int m_ammo, m_health, m_terminalVelocity;
	float m_hspeed, m_vspeed, m_moveSpeed, m_jumpSpeed, m_gravity;
	bool m_grounded;

	//methods
	void Update();
	bool Jump();
	bool Shoot();
	Vector MoveTowards(Actor* target, int speed); //returns a movement vector so the speed variables can be tweaked if needed

public:
	Character(Vector position, std::vector<std::string> sprite, int health);
	~Character();

	void SetAmmo(int ammo) { m_ammo = ammo; }
	void ChangeAmmo(int diff) { m_ammo += diff; }
	void SetHealth(int health) { m_health = health; }
	void ChangeHealth(int diff) { m_health += diff; }
	void SetSpeed(int speed) { m_moveSpeed = speed; }
	int GetAmmo() { return m_ammo; }
	int GetHealth() { return m_health; }
};