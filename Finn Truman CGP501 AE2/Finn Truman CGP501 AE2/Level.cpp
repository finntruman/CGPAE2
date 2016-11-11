#include "Level.h"
#include "Vector.h"
#include <math.h>

Level::Level(SDL_Renderer &renderer, int screenWidth, int screenheight)
	: p_renderer(&renderer), m_screenWidth(screenWidth), m_screenHeight(screenheight), m_viewportPos({ 0, 0 })
{
	//ALL ROWS MUST BE THE SAME LENGTH
	c_levelLayout.push_back("W.......................W");
	c_levelLayout.push_back("W.......................W");
	c_levelLayout.push_back("W.......................W");
	c_levelLayout.push_back("W.......................W");
	c_levelLayout.push_back("W.......WW..............W");
	c_levelLayout.push_back("W...........W..........W");
	c_levelLayout.push_back("W.......................W");
	c_levelLayout.push_back("WWWWWWWWWWWWWWWWWWWWWWWWW");

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
	m_viewportPos = { m_playerPos.x - m_screenWidth / 2, m_playerPos.y - m_screenHeight / 2 };

	float levelLayoutXMax = (c_levelLayout[0].length() - 1) * m_blockWidth;
	float levelLayoutYMax = (c_levelLayout.size() - 1) * m_blockHeight;

	if (m_viewportPos.x <= 0) m_viewportPos.x = 0;
	else if (m_viewportPos.x >= levelLayoutXMax) m_viewportPos.x = levelLayoutXMax;

	if (m_viewportPos.y <= 0) m_viewportPos.y = 0;
	else if (m_viewportPos.y >= levelLayoutYMax - m_screenHeight / 2) m_viewportPos.y = levelLayoutYMax - m_screenHeight / 2;

	DrawLevel();
}

void Level::DrawLevel()
{
	Vector screenSizeLevelSpace = WorldSpaceToLevelSpace(m_screenWidth + m_viewportPos.x, m_screenHeight + m_viewportPos.y);
	Vector viewportLevelSpace = WorldSpaceToLevelSpace(m_viewportPos);

	//the level goes through itself square by square
	for (int i = viewportLevelSpace.y; i < screenSizeLevelSpace.y; i++) //row for y
	{
		for (int j = viewportLevelSpace.x; j < screenSizeLevelSpace.x; j++) //column for x
		{
			if (i < 0 || i > c_levelLayout[0].length() - 1) break;
			if (j < 0 || j > c_levelLayout.size() - 1) break;

			if (c_levelLayout[j][i] == 'W') //if the level finds a wall it renders it
			{
				/*SDL_Surface* surface = SDL_CreateRGBSurface(0, m_blockWidth, m_blockHeight, 32, 0, 0, 0, 0);
				Uint32 m_blockColour = SDL_MapRGB(surface->format, 255, 0, 0);
				SDL_FillRect(surface, NULL, m_blockColour);
				m_texture = SDL_CreateTextureFromSurface(p_renderer, surface);
				SDL_FreeSurface(surface);*/

				SDL_Rect destRect = { j * m_blockWidth - m_viewportPos.x, i * m_blockHeight - m_viewportPos.y, m_blockWidth, m_blockHeight };
				SDL_RenderCopy(p_renderer, m_texture, NULL, &destRect);
			}
		}
	}
}

char Level::GetLevelCoord(int x, int y)
{
	//row uses y
	//column uses x
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
