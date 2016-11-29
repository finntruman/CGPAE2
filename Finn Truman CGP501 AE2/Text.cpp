#include "Text.h"

Text::Text(int x, int y, std::string text, SDL_Renderer &renderer, TTF_Font* font, SDL_Colour colour)
	: m_x(x), m_y(y), m_text(text), p_renderer(&renderer), m_colour(colour), m_font(font)
{
	Update();
}

Text::~Text()
{
	p_renderer = nullptr;
}

void Text::Update()
{
	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;

	int textW = 0;
	int textH = 0;

	surface = TTF_RenderText_Solid(m_font, m_text.c_str(), m_colour);

	if (!surface) printf("SURFACE for font not loaded!\n%s\n", SDL_GetError());
	else
	{
		texture = SDL_CreateTextureFromSurface(p_renderer, surface);
		if (!texture) printf("TEXTURE for font not loaded!\n%s\n", SDL_GetError());
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
			SDL_Rect textRect = { m_x, m_y, textW, textH };

			SDL_RenderCopy(p_renderer, texture, NULL, &textRect);
		}
	}

	if (texture) SDL_DestroyTexture(texture);
	if (surface) SDL_FreeSurface(surface);
}