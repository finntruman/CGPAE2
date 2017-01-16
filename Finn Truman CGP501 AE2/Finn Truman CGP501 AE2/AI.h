#pragma once
#include "Character.h"
#include "Player.h"

enum STATES_ENEMY
{
	STT_WANDERING, STT_HOSTILE
}; //cannot call the WANDERING state IDLE as there is already an enum value called IDLE somewhere else (the player class)

class AI : public Character
{
protected:
	Player* p_player;
	STATES_ENEMY m_stateMachine;

	float DistanceToPlayer();

public:
	AI(GameManager &manager, SDL_Renderer &renderer, Level &levelLayout, Vector position, std::vector<std::string> sprite, int health);
	~AI();
	void Update();
};

