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
	p_textManager = new TextManager(*m_renderer);
	//CreateMenu({ "Hello", "World", "The third test option" }, "DejaVu small");
	p_level = new Level(*m_renderer, 640, 480);
	CreatePlayer({ 70, 635 }, "assets/player.bmp", 100, 100);
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
	TTF_CloseFont(m_ui_font);
	TTF_Quit();
}

void GameManager::Update()
{
	SDL_RenderClear(m_renderer); //wipe the display. this must always go at the START of the Update function.
	int startTicks = SDL_GetTicks();

	//update classes
	p_input->Update();
	p_textManager->Update();
	if (p_menu) p_menu->Update();
	if (p_level) p_level->Update();
	p_level->SetPlayerPos(p_player->GetPosition());
	if (p_player) p_player->Update();

	//UI
	DrawUI({
		"Health: " + std::to_string(p_player->GetHealth()),
		"Ammo: " + std::to_string(p_player->GetAmmo())
	});

	int endTicks = SDL_GetTicks() - startTicks;
	if (endTicks < MILLISECS_PER_FRAME) SDL_Delay(MILLISECS_PER_FRAME - endTicks); //caps the framerate to 60

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

bool GameManager::CheckEscape()
{
	return p_input->KeyPressed(KEY_ESCAPE);
}