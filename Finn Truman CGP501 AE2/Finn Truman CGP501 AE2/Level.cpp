#include "Level.h"
#include "Vector.h"
#include <math.h>

Level::Level(SDL_Renderer &renderer, int screenWidth, int screenheight)
	: p_renderer(&renderer), m_screenWidth(screenWidth), m_screenHeight(screenheight), m_viewportPos({ 0, 0 })
{
	//ALL ROWS MUST BE THE SAME LENGTH
	c_levelLayout.push_back("W..................W");
	c_levelLayout.push_back("W..................W");
	c_levelLayout.push_back("W.WWWWWWWWWWWWWWW..W");
	c_levelLayout.push_back("W.................WW");
	c_levelLayout.push_back("W................W.W");
	c_levelLayout.push_back("WW..........W..W...W");
	c_levelLayout.push_back("WWWW...............W");
	c_levelLayout.push_back("WWWWWWWWWWWWWWWWWWWW");

	m_viewportXMax = (c_levelLayout[0].length()) * m_blockWidth - m_screenWidth;
	m_viewportYMax = (c_levelLayout.size()) * m_blockHeight - m_screenHeight;
	m_screenSizeLevelSpace = WorldSpaceToLevelSpace(m_screenWidth, m_screenHeight); //this gets the screen's size in LevelSpace

	//this is all the start process to get a texture for the walls
	SDL_Surface* surface = SDL_CreateRGBSurface(0, m_blockWidth, m_blockHeight, 32, 0, 0, 0, 0);
	Uint32 m_blockColour = SDL_MapRGB(surface->format, 255, 0, 0);
	SDL_FillRect(surface, NULL, m_blockColour);
	m_texture = SDL_CreateTextureFromSurface(p_renderer, surface);
	SDL_FreeSurface(surface);
}

Level::~Level()
{
	SDL_DestroyTexture(m_texture);
	p_renderer = nullptr;
}

void Level::Update()
{
	m_viewportPos = { m_playerPos.x - m_screenWidth / 2, m_playerPos.y - m_screenHeight / 2 }; //this keeps the player centered on the viewport

	m_viewportPos.x = Clamp(m_viewportPos.x, 0, m_viewportXMax); //this clamps the viewport so it doesn't go off any of the four sides of the play area
	m_viewportPos.y = Clamp(m_viewportPos.y, 0, m_viewportYMax);

	DrawLevel();
}

void Level::DrawLevel()
{
	Vector viewportLevelSpace = WorldSpaceToLevelSpace(m_viewportPos); //the viewport's position in LevelSpace
	int viewportWidthLimit = Clamp(viewportLevelSpace.x + m_screenSizeLevelSpace.x + 1, 0, c_levelLayout[0].length()); //thes two variables are the limits to how much the level renders
	int viewportHeightLimit = Clamp(viewportLevelSpace.y + m_screenSizeLevelSpace.y + 1, 0 , c_levelLayout.size());

	//the level goes through itself square by square
	for (int i = viewportLevelSpace.y; i < m_screenSizeLevelSpace.y; i++) //row for y
	{
		for (int j = viewportLevelSpace.x; j < viewportWidthLimit; j++) //column for x
		{
			if (c_levelLayout[i][j] == 'W') //if the level finds a wall it renders it
			{
				SDL_Rect destRect = { j * m_blockWidth - m_viewportPos.x, i * m_blockHeight - m_viewportPos.y, m_blockWidth, m_blockHeight };
				SDL_RenderCopy(p_renderer, m_texture, NULL, &destRect);
			}
		}
	}

	//This level drawing code draws the whole level, perfectly
	/*
	for (int i = 0; i < c_levelLayout.size(); i++) //row for y
	{
		for (int j = 0; j < c_levelLayout[0].length(); j++) //column for x
		{
			if (c_levelLayout[i][j] == 'W') //if the level finds a wall it renders it
			{
				SDL_Rect destRect = { j * m_blockWidth - m_viewportPos.x, i * m_blockHeight - m_viewportPos.y, m_blockWidth, m_blockHeight };
				SDL_RenderCopy(p_renderer, m_texture, NULL, &destRect);
			}
		}
	}*/
}

int Level::Clamp(int toClamp, int min, int max)
{
	if (toClamp < min) return min;
	else if (toClamp > max) return max;
}

char Level::GetLevelCoord(int x, int y)
{
	//row uses y
	//column uses x
	if (y < 0 || y > c_levelLayout.size() - 1) return '.'; //returns '.' if the coordinates fall outside of the level
	if (x < 0 || x > c_levelLayout[0].length() - 1)  return '.';
	return c_levelLayout[y][x]; //row column
}

char Level::GetLevelCoord(Vector position)
{
	//return GetLevelCoord(round(position.x), round(position.y));
	return GetLevelCoord(position.x, position.y);
}

Vector Level::WorldSpaceToLevelSpace(int x, int y)
{
	return Vector(x, y) / m_blockHeight;
}

Vector Level::WorldSpaceToLevelSpace(Vector position)
{
	return WorldSpaceToLevelSpace(position.x, position.y);
}
