#include "GameManager.h"

#include "Input.h"
#include "TextManager.h"
#include "Menu.h"
#include "Level.h"
#include "Player.h"

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
			SDL_RENDERER_PRESENTVSYNC);			//renderer behaviour flags

		if (!m_renderer)
		{
			printf("RENDERER initialisation failed: %s\n", SDL_GetError());
			printf("Press any key to continue\n");
			fflush(stdin);
			getchar();
			return;
		}
	}
	
	//now we've finished SDL setup, make game objects
	p_input = new Input();
	p_textManager = new TextManager(*m_renderer);
	//CreateMenu({ "Hello", "World", "The third test option" }, "DejaVu small");
	p_level = new Level(*m_renderer, 640, 480);
	CreatePlayer({ 128, 64 }, "assets/player.bmp", 100, 100);
}

GameManager::~GameManager()
{
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

	if (p_menu)
	{
		delete p_menu;
		p_menu = nullptr;
	}

	if (p_textManager)
	{
		delete p_textManager;
		p_textManager = nullptr;
	}

	if (p_input)
	{
		delete p_input;
		p_input = nullptr;
	}

	SDL_Quit();
}

void GameManager::Update()
{
	SDL_RenderClear(m_renderer); //wipe the display. this must always go at the START of the Update function.

	//update classes
	p_input->Update();
	p_textManager->Update();
	if (p_menu) p_menu->Update();
	if (p_level) p_level->Update();
	p_level->SetPlayerPos(p_player->GetPosition());
	if (p_player) p_player->Update();

	SDL_RenderPresent(m_renderer); //show what we've drawn. this must always go at the END of the Update function.
}

void GameManager::CreateMenu(std::vector<std::string> options, std::string font)
{
	p_menu = new Menu(*this, *m_renderer, *p_textManager, options, font);
}

void GameManager::CreatePlayer(Vector position, std::string sprite, int ammo, int health)
{
	if (p_player) return;
	std::vector<std::string> sprites;
	sprites.push_back(sprite);
	p_player = new Player(*m_renderer, *p_level, *p_input, position, sprites);
	p_player->SetAmmo(ammo);
	p_player->SetHealth(health);
}

bool GameManager::CheckEscape()
{
	return p_input->KeyPressed(KEY_ESCAPE);
}