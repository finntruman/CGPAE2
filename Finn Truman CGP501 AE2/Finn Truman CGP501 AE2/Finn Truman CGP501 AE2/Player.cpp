#include "Player.h"
#include "Input.h"

Player::Player(SDL_Renderer &renderer, Level &levelLayout, Input &input, Vector position, std::vector<std::string> sprite)
	: Character(renderer, levelLayout, position, sprite), p_input(&input)
{
}

Player::~Player()
{
}

void Player::Update()
{
	//check for key presses
	if (p_input->KeyHeld(KEY_LEFT)) m_hspeed -= m_moveSpeed;
	if (p_input->KeyHeld(KEY_RIGHT)) m_hspeed += m_moveSpeed;
	if (p_input->KeyHeld(KEY_UP)) Jump();

	//check for state changes
	if (m_hspeed == 0) m_stateMachine = STT_IDLE;
	else m_stateMachine = STT_MOVING;

	//check for the state itself
	switch (m_stateMachine)
	{
	case STT_IDLE:
		State_Idle();
		break;

	case STT_MOVING:
		State_Moving();
		break;
	}

	Character::Update();
}

void Player::State_Idle()
{
	if (p_sprite.GetSprite() != "assets/player.bmp")
	{
		p_sprite.ChangeSprite("assets/player.bmp");
		p_sprite.SetSpeed(1);
	}
}

void Player::State_Moving()
{
	if (p_sprite.GetSprite().compare(7, 10, "player_run") != 0) //if the 10 characters after the 7th are not "player_run"
	{
		std::vector<std::string> newSpriteSequence; //creates a new vector of strings...
		for (int i = 2; i >= 0; i--)
		{
			newSpriteSequence.push_back("assets/player_run" + std::to_string(i) + ".bmp"); //and fills it with all of the "player_run" animation frames
		}
		p_sprite.ChangeSprite(newSpriteSequence); //then changes its sprite
		p_sprite.SetSpeed(5);
	}
}