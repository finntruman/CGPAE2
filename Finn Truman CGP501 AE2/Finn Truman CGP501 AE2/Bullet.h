#pragma once
#include "Collision.h"

class Level;

class Bullet : public Collision
{
private:
	int m_speed;

public:
	Bullet(Vector position, std::vector<std::string> sprite, int speed);
	Bullet(Vector position, int speed);
	~Bullet();
	void Update();
};