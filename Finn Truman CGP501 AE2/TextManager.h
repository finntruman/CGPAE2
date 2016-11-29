#pragma once
#include <vector>
#include <map>
#include "SDL_ttf.h"

class Text;

class TextManager
{
private:
	SDL_Renderer* p_renderer;

	//containers
	std::map<std::string, TTF_Font*> c_fonts;
	std::vector<Text> c_texts;

public:
	TextManager(SDL_Renderer &renderer);
	~TextManager();

	//methods
	void Update();
	void CreateText(int x, int y, std::string text, std::string font, SDL_Colour colour = { 255, 255, 255, 255 });
	int FontHeight(std::string font) { return TTF_FontHeight(c_fonts[font]); }
};

