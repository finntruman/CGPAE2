#pragma once
#include "Character.h"

class Input;
class Level;

enum STATES_PLAYER
{
	STT_IDLE, STT_MOVING
};

class Player : public Character
{
private:
	Input* p_input;
	STATES_PLAYER m_stateMachine;

	bool m_canShoot;

	//states
	void State_Idle();
	void State_Moving();

public:
	Player(SDL_Renderer &renderer, Level &levelLayout, Input &input, Vector position, std::vector<std::string> sprite);
	~Player();

	void Update();
};

