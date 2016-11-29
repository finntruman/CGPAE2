#pragma once
#include <string>
#include <vector>

#include "SDL_ttf.h"

class Text
{
private:
	//pointers
	SDL_Renderer* p_renderer;

	//members
	int m_x, m_y;
	std::string m_text;
	TTF_Font* m_font;
	SDL_Colour m_colour;

public:
	Text(int x, int y, std::string text, SDL_Renderer &renderer, TTF_Font* font, SDL_Colour colour = { 255, 255, 255, 255 });
	~Text();

	//methods
	void Update();
	std::string GetText() { return m_text; }
};