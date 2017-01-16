#pragma once
#include "Character.h"
#include <vector>

class Input;
class Level;

enum STATES_PLAYER
{
	STT_IDLE, STT_MOVING
};

class Player : public Character
{
private:
	STATES_PLAYER m_stateMachine;

	bool m_canShoot;

	//states
	void State_Idle();
	void State_Moving();

public:
	Player(Vector position, std::vector<std::string> sprite);
	~Player();

	void Update();
};