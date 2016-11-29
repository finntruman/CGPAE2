#include "TextManager.h"
#include "Text.h"

TextManager::TextManager(SDL_Renderer &renderer)
	: p_renderer(&renderer)
{
	c_fonts["DejaVu small"] = TTF_OpenFont("assets/DejaVuSans.ttf", 15);
}

TextManager::~TextManager()
{
	if (p_renderer) p_renderer = nullptr;
}

void TextManager::Update()
{
	for (int i = 0; i < c_texts.size(); i++) c_texts[i].Update();
}

void TextManager::CreateText(int x, int y, std::string text, std::string font, SDL_Colour colour)
{
	c_texts.push_back(Text(x, y, text, *p_renderer, c_fonts[font], colour));
}
