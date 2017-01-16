#include "Player.h"
#include "Input.h"

Player::Player(Vector position, std::vector<std::string> sprite)
	: Character(position, sprite, 100), m_canShoot(true)
{
	//the tip of the player's gun adds to the sprite's maximum width, which I found to be irritating, as one would measure one's collision width by their body
	//this function narrows the collision width of the player slightly
	m_sprite.ChangeCollisionShape(35, m_sprite.GetSpriteHeight());
}

Player::~Player()
{
}

void Player::Update()
{
	//check for key presses
	if (p_input->KeyHeld(KEY_LEFT))
	{
		m_hspeed -= m_moveSpeed;
		m_facing = SDL_FLIP_HORIZONTAL;
	}
	if (p_input->KeyHeld(KEY_RIGHT))
	{
		m_hspeed += m_moveSpeed;
		m_facing = SDL_FLIP_NONE;
	}
	if (p_input->KeyHeld(KEY_UP)) Jump();
	//if (p_input->KeyPressed(KEY_SHOOT)) Shoot();
	if (p_input->KeyPressed(KEY_SHOOT))
	{
		if (m_canShoot) Shoot();
		m_canShoot = false;
	}
	if (p_input->KeyUp(KEY_SHOOT))
	{
		m_canShoot = true;
	}

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
	if (m_sprite.GetSprite() != "assets/player.bmp")
	{
		m_sprite.ChangeSprite("assets/player.bmp");
		m_sprite.SetSpeed(1);
	}
}

void Player::State_Moving()
{
	if (m_sprite.GetSprite().compare(7, 10, "player_run") != 0) //if the 10 characters after the 7th are not "player_run"
	{
		std::vector<std::string> newSpriteSequence; //creates a new vector of strings...
		for (int i = 2; i >= 0; i--)
		{
			newSpriteSequence.push_back("assets/player_run" + std::to_string(i) + ".bmp"); //and fills it with all of the "player_run" animation frames
		}
		m_sprite.ChangeSprite(newSpriteSequence); //then changes its sprite
		m_sprite.SetSpeed(5);
	}
}