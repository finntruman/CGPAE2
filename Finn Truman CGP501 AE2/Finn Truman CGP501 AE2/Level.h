#pragma once
#include "GameObject.h"
#include "Vector.h"
#include <vector>
#include <string>

//struct Vector;

/*
	The Level class keeps track of the layout of the level and the viewport

	There are two types of space:
	WorldSpace - The space that has its coordinates go into the hundreds. This is the space that the Actor vectors are measured in
	LevelSpace - The level vectors are only a few squares by a few squares, so level space will usually only go into the double digits
*/

enum LevelTextures
{
	T_DIRT0, T_DIRT1
};

class Level : public GameObject
{
private:
	//members
	SDL_Texture* m_texture; //this texture is to render the walls
	std::vector<SDL_Texture*> c_textures;

	std::vector<std::string> c_levelLayout; //this is the vector that knows where everything is in the level. this is what works in LevelSpace
	LevelTextures leveltextures;
	const int m_blockWidth = 64, m_blockHeight = 64; //these sizes are very important, as they keep track of what the conversion rate is from WorldSpace to LevelSpace

	//viewport stuff
	Vector m_viewportPos;
	Vector m_playerPos;
	int m_screenWidth, m_screenHeight;
	float m_viewportXMax, m_viewportYMax; //the maximum X and Y the viewport can go to
	Vector m_screenSizeLevelSpace;

	//methods
	void DrawLevel();

public:
	Level(int screenWidth, int screenheight);
	~Level();
	
	void Update();
	char GetLevelCoord(int x, int y); //returns the char at that point of the map in LevelSpace
	char GetLevelCoord(Vector position); //Parameters MUST BE given in LevelSpace

	Vector WorldSpaceToLevelSpace(int x, int y);
	Vector WorldSpaceToLevelSpace(Vector position);
	Vector LevelSpaceToWorldSpace(int x, int y);
	Vector LevelSpaceToWorldSpace(Vector position);

	int GetHeight() { return c_levelLayout.size(); } //returns the height of the map in LevelSpace
	int GetWidth() { return c_levelLayout[0].length(); } //returns the width of the map in LevelSpace
	std::vector<std::string> GetLevel() { return c_levelLayout; } //returns the level itself as a vector of strings
	Vector GetViewportPos() { return m_viewportPos; } //returns the WorldSpace position of the viewport
	void SetPlayerPos(Vector player) { m_playerPos = player; }
	//void SetViewportPos(Vector newPos) { m_viewportPos = newPos; }
};