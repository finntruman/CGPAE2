#include "GameManager.h"

#include <math.h>
#include <algorithm>

#include "Input.h"
#include "Level.h"
#include "Player.h"
#include "EnemySoldier.h"
#include "Bullet.h"
#include "Collectible.h"

GameManager::GameManager()
{
	//the 'if (true)' is simply here so all the SDL stuff can be minimized
	if (true)
	{
		//start up
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();

		//create the window
		m_window = SDL_CreateWindow(
			"Operation Pegasus",	//title
			250, 50,			//initial x and y position
			640, 480,			//width and height in pixels
			0);					//window behaviour flags

		if (!m_window)
		{
			printf("WINDOW initialisaton failed: %s\n", SDL_GetError());
			printf("Press any key to continue\n");
			fflush(stdin); //flush the buffer
			getchar();
			return;
		}

		//create renderer
		m_renderer = SDL_CreateRenderer(
			m_window,	//link the renderer to our new created window
			-1,			//index rendering driver
			NULL);			//renderer behaviour flags

		if (!m_renderer)
		{
			printf("RENDERER initialisation failed: %s\n", SDL_GetError());
			printf("Press any key to continue\n");
			fflush(stdin);
			getchar();
			return;
		}

		m_ui_font = TTF_OpenFont("assets/DejaVuSans.ttf", 20);
	}
	
	//now we've finished SDL setup, make game objects
	p_input = new Input();
	p_level = new Level(*m_renderer, 640, 480);
	CreatePlayer({ 70, 635 }, "assets/player.bmp", 100, 100);
	SpawnEnemy({ 840, 512 }, 1, 10);
}

GameManager::~GameManager()
{
	std::for_each(p_collectibles.begin(), p_collectibles.end(), [](Collectible* collectible) { delete collectible; }); //I use a lambda expression to make a quick, throwaway function to delete the collectibles

	std::for_each(p_enemies.begin(), p_enemies.end(), [](EnemySoldier* enemy) { delete enemy; }); //same for enemies

	std::for_each(p_bullets.begin(), p_bullets.end(), [](Bullet* bullet) { delete bullet; }); //and bullets

	if (p_player)
	{
		delete p_player;
		p_player = nullptr;
	}

	if (p_level)
	{
		delete p_level;
		p_level = nullptr;
	}

	if (p_input)
	{
		delete p_input;
		p_input = nullptr;
	}

	SDL_Quit();
	TTF_CloseFont(m_ui_font);
	TTF_Quit();
}

void GameManager::Update()
{
	SDL_RenderClear(m_renderer); //wipe the display. this must always go at the START of the Update function.
	int startTicks = SDL_GetTicks(); //get the number of ticks since SDL has been launched

	//##UPDATE CLASSES##
	p_input->Update();
	//if (p_menu) p_menu->Update();
	if (p_level) p_level->Update();
	p_level->SetPlayerPos(p_player->GetPosition());
	if (p_player) p_player->Update();

	//BULLETS
	for (int i = 0; i < p_bullets.size(); i++)
	{
		p_bullets[i]->Update();

		Vector bulletPos = p_bullets[i]->GetPosition();

		//WALL/OOUT OF BOUNDS DETECTION
		if (
			CollisionPoint_Map(bulletPos) //if there is a collision where the bullet is (precise sprite collision is unecesarry)
			|| p_bullets[i]->GetPosition().x < 0 //or if the bullet's x is less than 0 (off the left side of the level)
			|| p_bullets[i]->GetPosition().x > p_level->LevelSpaceToWorldSpace(p_level->GetWidth(), 0).x //or if the bullet's x is greater than the width of the level
			)
		{
			delete p_bullets[i];
			p_bullets.erase(p_bullets.begin() + i); //deleting a pointer's memory still means that that element in the vector is being taken up, it's just empty, so erasing the element reorganises the vector
			break; //break the for loop since the bullet has been deleted, it will crash if it tries to detect collision again with enemies
		}

		//PLAYER COLLISION
		if (DistanceTo(bulletPos, p_player->GetPosition()) <= 10)
		{
			if (CollisionSprite_Object(p_bullets[i], p_player))
			{
				p_player->ChangeHealth(-5);
				delete p_bullets[i];
				p_bullets.erase(p_bullets.begin() + i);
				break;
			}
		}

		//ENEMY COLLISION
		for (int j = 0; j < p_enemies.size(); j++)
		{
			if (DistanceTo(bulletPos, p_enemies[j]->GetPosition()) <= 10) //10 is a magic number that is the speed of the bullet, bit of bad design. This is here since, if the target is not within range of the bullet to even hit it at its speed, what's the point in checking collision?
			{
				if (CollisionSprite_Object(p_bullets[i], p_enemies[j]))
				{
					p_enemies[j]->ChangeHealth(-5); //5 is another magic number that is the bullet's damage
					delete p_bullets[i];
					p_bullets.erase(p_bullets.begin() + i); //it's because of this bit of code here that it'd be better for me to have used a list instead of a vector for the bullets
				}
			}
		}
	}

	//ENEMIES
	for (int i = 0; i < p_enemies.size(); i++)
	{
		if (p_enemies[i]->GetHealth() <= 0) KillEnemy(p_enemies[i]);
		else p_enemies[i]->Update();
	}

	//COLLECTIBLES
	for (int i = 0; i < p_collectibles.size(); i++)
	{
		p_collectibles[i]->Update();
		if (DistanceTo(p_collectibles[i]->GetPosition(), p_player->GetPosition()) <= p_collectibles[i]->GetSprite()->GetCollisionWidth())
		{
			if (CollisionSprite_Object(p_collectibles[i], p_player))
			{
				if (p_collectibles[i]->ReturnType() == "ammo")
				{
					p_player->ChangeAmmo(5);
				}
				else if (p_collectibles[i]->ReturnType() == "health")
				{
					p_player->ChangeHealth(5);
				}
				delete p_collectibles[i];
				p_collectibles.erase(p_collectibles.begin() + i);
			}
		}
	}
	/*
		I would have liked to make it the player's responsibility to look for collectible collisions, change stats and delete the collectible.
		But due to the limitations of how I programmed it, that was not possible. This could've all been avoided if I had implimented the GameObject class I discussed in the documentation.
	*/

	//##UI##
	DrawUI({
		"Health: " + std::to_string(p_player->GetHealth())
		,"Ammo: " + std::to_string(p_player->GetAmmo()), " "
		/*,"X: " + std::to_string(p_player->GetPosition().x)
		,"Y: " + std::to_string(p_player->GetPosition().y)*/ //removing this code blocvk displays the player's X and Y on-screen. Used for debug purposes.
	});

	int endTicks = SDL_GetTicks() - startTicks; //how many ticks have passed since we last got the ticks?
	if (endTicks < MILLISECS_PER_FRAME) SDL_Delay(MILLISECS_PER_FRAME - endTicks); //if not enough ticks have passed to get a 60 FPS framerate, freeze the game until there has
	//capping the framerate is important as there isn't enough strain on the game to make it run at a slow enough rate

	SDL_RenderPresent(m_renderer); //show what we've drawn. this must always go at the END of the Update function.
}

void GameManager::CreateMenu(std::vector<std::string> options, std::string font)
{
	//p_menu = new Menu(*this, *m_renderer, *p_textManager, options, font);
}

void GameManager::CreatePlayer(Vector position, std::string sprite, int ammo, int health)
{
	if (p_player) return;
	std::vector<std::string> sprites;
	sprites.push_back(sprite);
	p_player = new Player(*this, *m_renderer, *p_level, *p_input, position, sprites);
	p_player->SetAmmo(ammo);
	p_player->SetHealth(health);
}

void GameManager::SpawnEnemy(Vector position, int health, int points, std::string sprite)
{
	p_enemies.push_back(new EnemySoldier(*this, *m_renderer, *p_level, position, { sprite }, 10, 1));
}

void GameManager::CreateCollectible(Vector position, int type)
{
	//0 = health
	//1 = ammo
	p_collectibles.push_back(new Collectible(*m_renderer, *p_level, position, type));
}

void GameManager::UpdateText(int x, int y, std::string msg, SDL_Color colour)
{
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	int textW = 0;
	int textH = 0;

	surface = TTF_RenderText_Solid(m_ui_font, msg.c_str(), colour);
	if (!surface)
	{
		//surface not loaded
		printf("SURFACE for font not loaded!\n");
		printf("%s\n", SDL_GetError());
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(m_renderer, surface);
		if (!texture)
		{
			printf("TEXTURE for font not loaded!\n");
			printf("&s\n", SDL_GetError());
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
			SDL_Rect textRect = { x, y, textW, textH };
			SDL_RenderCopy(m_renderer, texture, NULL, &textRect);
		}
	}

	if (texture) SDL_DestroyTexture(texture);
	if (surface) SDL_FreeSurface(surface);
}

void GameManager::DrawUI(std::vector<std::string> UIElements)
{
	int padding = 25;
	for (int i = 0; i < UIElements.size(); i++)
	{
		UpdateText(20, 10 + padding * i, UIElements[i]);
	}
}

void GameManager::KillEnemy(EnemySoldier* toKill)
{
	for (int i = 0; i < p_enemies.size(); i++)
	{
		if (toKill == p_enemies[i])
		{
			CreateCollectible(p_enemies[i]->GetPosition(), 1);
			delete p_enemies[i];
			p_enemies.erase(p_enemies.begin() + i);
			return;
		}
	}
}

bool GameManager::CheckEscape()
{
	return p_input->KeyPressed(KEY_ESCAPE);
}

float GameManager::DistanceTo(Vector point1, Vector point2)
{
	Vector pointB(point1.x, point2.y);

	float AtoB = pointB.x - point1.x;
	float BtoC = point2.y - pointB.y;

	//sqrt(A*A + B*B)
	return std::sqrt(AtoB*AtoB + BtoC*BtoC);
}

void GameManager::AddBullet(Bullet &bullet)
{
	p_bullets.push_back(&bullet);
}

bool GameManager::CollisionPoint_Map(float x, float y)
{
	Vector mapVector = p_level->WorldSpaceToLevelSpace(x, y);
	if (p_level->GetLevelCoord(mapVector) == '.')
	{
		return false; //it was a dot, no collision, return false
	}
	else return true; //it was something other than a dot, collision, return true
}

bool GameManager::CollisionPoint_Map(Vector travel)
{
	return CollisionPoint_Map(travel.x, travel.y);
}

bool GameManager::CollisionSprite_Object(Actor* collision1, Actor* collision2)
{
	float spr1_L, spr1_T, spr1_R, spr1_B, spr2_L, spr2_T, spr2_R, spr2_B;

	spr1_L = collision1->GetPosition().x;
	spr1_R = spr1_L + collision1->GetSprite()->GetCollisionWidth() - 1;
	spr1_T = collision1->GetPosition().y;
	spr1_B = spr1_T + collision1->GetSprite()->GetCollisionHeight() - 1;

	spr2_L = collision2->GetPosition().x;
	spr2_R = spr2_L + collision2->GetSprite()->GetCollisionWidth() - 1;
	spr2_T = collision2->GetPosition().y;
	spr2_B = spr2_T + collision2->GetSprite()->GetCollisionHeight() - 1;

	if (spr1_L < spr2_R &&
		spr1_R > spr2_L &&
		spr1_T < spr2_B &&
		spr1_B > spr2_T)
	{
		return true;
	}
	else return false;
}