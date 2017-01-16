#pragma once
#include <string>
#include <vector>
#include <stdio.h>

#include "SDL.h"
#include "SDL_ttf.h"

#include "GameObject.h"

struct SDL_Window;
struct SDL_Renderer;

class Actor;
class Input;
class Level;
class Player;
class EnemySoldier;
class Bullet;
class Collectible;
struct Vector;

class GameManager : public GameObject
{
private:
	//SDL stuff
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	TTF_Font* m_ui_font;

	//framerate stuff
	const int SCREEN_FPS = 60;
	const int MILLISECS_PER_FRAME = 1000 / SCREEN_FPS;

	//pointers
	Player* p_player;
	std::vector<Bullet*> p_bullets;
	std::vector<EnemySoldier*> p_enemies;
	std::vector<Collectible*> p_collectibles;

	//methods
	void CreateMenu(std::vector<std::string> options, std::string font); //the menu works by having an array of strings to draw, and it needs to know what font to draw them in. So CreateMenu takes a vector of strings and a font
	void CreatePlayer(Vector position, std::string sprite, int ammo, int health);
	void SpawnEnemy(Vector position, int health, int points, std::string sprite = "assets/player.bmp");
	void CreateCollectible(Vector position, int type);

public:
	GameManager();
	~GameManager();

	//methods
	void Update();
	void UpdateText(int x, int y, std::string msg, SDL_Color colour = { 255,255,255 });
	void DrawUI(std::vector<std::string> UIElements);
	void KillEnemy(EnemySoldier* toKill);
	bool CheckEscape();

	void AddBullet(Bullet &bullet); //the reason this is called AddBullet and not SpawnBullet is because it simply adds the bullet to the vector, as the bullet is already created in the Character that called it
};