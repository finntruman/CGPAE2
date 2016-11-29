#pragma once
#include "SDL.h"
#include "Vector.h"
#include <vector>
#include <string>

//struct Vector;

/*
	There are two types of space:
	WorldSpace - The space that has its coordinates go into the hundreds. This is the space that the Actor vectors are measured in
	LevelSpace - The level vectors are only a few squares by a few squares, so level space will usually only go into the double digits
*/

enum LevelTextures
{
	T_DIRT0, T_DIRT1
};

class Level
{
private:
	SDL_Renderer* p_renderer;
	SDL_Texture* m_texture; //this texture is to render the walls

	std::vector<std::string> c_levelLayout; //this is the vector that knows where everything is in the level. this is what works in LevelSpace
	LevelTextures leveltextures;
	std::vector<SDL_Texture*> c_textures;
	const int m_blockWidth = 64, m_blockHeight = 64; //these sizes are very important, as they keep track of what the conversion rate is from WorldSpace to LevelSpace

	//viewport stuff
	Vector m_viewportPos;
	Vector m_playerPos;
	int m_screenWidth, m_screenHeight;
	float m_viewportXMax, m_viewportYMax;
	Vector m_screenSizeLevelSpace;

	void DrawLevel();

public:
	Level(SDL_Renderer &renderer, int screenWidth, int screenheight);
	~Level();
	
	void Update();
	char GetLevelCoord(int x, int y); //returns the char at that point of the map in LevelSpace
	char GetLevelCoord(Vector position);

	Vector WorldSpaceToLevelSpace(int x, int y);
	Vector WorldSpaceToLevelSpace(Vector position);

	int Clamp(int toClamp, int min, int max);

	int GetHeight() { return c_levelLayout.size(); } //returns the height of the map in LevelSpace
	int GetWidth() { return c_levelLayout[0].length(); } //returns the width of the map in LevelSpace
	std::vector<std::string> GetLevel() { return c_levelLayout; } //returns the level itself as a vector of strings
	Vector GetViewportPos() { return m_viewportPos; } //returns the WorldSpace position of the viewport
	void SetPlayerPos(Vector player) { m_playerPos = player; }
	//void SetViewportPos(Vector newPos) { m_viewportPos = newPos; }
};