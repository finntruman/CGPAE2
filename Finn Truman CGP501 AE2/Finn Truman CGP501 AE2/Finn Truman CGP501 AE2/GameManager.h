#pragma once
#include <string>
#include <vector>
#include <stdio.h>

#include "SDL.h"
#include "SDL_ttf.h"

struct SDL_Window;
struct SDL_Renderer;

class Input;
class TextManager;
class Menu;
class Level;
class Player;
struct Vector;

class GameManager
{
private:
	//SDL stuff
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	//framerate stuff
	const int SCREEN_FPS = 60;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
	//LTimer fpsTimer;

	//pointers
	Input* p_input;
	TextManager* p_textManager;
	Menu* p_menu;
	Level* p_level;
	Player* p_player;

	//methods
	void CreateMenu(std::vector<std::string> options, std::string font); //the menu works by having an array of strings to draw, and it needs to know what font to draw them in. So CreateMenu takes a vector of strings and a font
	void CreatePlayer(Vector position, std::string sprite, int ammo, int health);

public:
	GameManager();
	~GameManager();

	//methods
	void Update();
	bool CheckEscape();
};