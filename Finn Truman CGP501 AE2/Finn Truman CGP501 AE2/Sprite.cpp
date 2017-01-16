#include "Sprite.h"
#include "GameObject.h"

Sprite::Sprite()
{}

Sprite::~Sprite()
{
	if (p_bitmapTexture) SDL_DestroyTexture(p_bitmapTexture);
	if (p_bitmapSurface) SDL_FreeSurface(p_bitmapSurface);
	p_parent = nullptr;
}

void Sprite::Initialise(Actor &parent, std::vector<std::string> sprites)
{
	p_parent = &parent;
	c_spriteSequence = sprites;
	m_spriteFrame = 0;
	m_animationSpeed = 1;
	m_animationDelay = 0;
	m_useSpriteCollision = true;
	ChangeImage(c_spriteSequence[0]);
}

void Sprite::ChangeSprite(std::vector<std::string> images)
{
	c_spriteSequence.clear(); //clears the sprite we have
	c_spriteSequence = images; //sets the sprite to the one that's just been passed
	ChangeImage(c_spriteSequence[0]); //automatically resets the sprite's sequence back to the first frame
}

void Sprite::ChangeSprite(std::string sprite)
{
	c_spriteSequence.clear(); //clears the sprite we have
	c_spriteSequence.push_back(sprite); //and simply puts the new images into the sequence
	ChangeImage(sprite);
}

void Sprite::ChangeImage(std::string sprite)
{
	m_image = sprite;
	if (p_bitmapTexture) SDL_DestroyTexture(p_bitmapTexture);
	if (p_bitmapSurface) SDL_FreeSurface(p_bitmapSurface);

	//create the bitmap surface
	p_bitmapSurface = SDL_LoadBMP(m_image.c_str());
	if (!p_bitmapSurface)
	{
		//bitmap not loaded
		printf("SURFACE for bitmap '%s' not loaded!\n%s\n", m_image.c_str(), SDL_GetError());
	}
	else
	{
		m_spriteHeight = p_bitmapSurface->h;
		m_spriteWidth = p_bitmapSurface->w;
		if (m_useSpriteCollision)
		{
			m_collisionHeight = m_spriteHeight;
			m_collisionWidth = m_spriteWidth;
		}

		//transparency
		Uint32 colourKey = SDL_MapRGB(p_bitmapSurface->format, 255, 0, 255);
		SDL_SetColorKey(p_bitmapSurface, SDL_TRUE, colourKey);

		//create the texture
		p_bitmapTexture = SDL_CreateTextureFromSurface(p_renderer, p_bitmapSurface);
		if (!p_bitmapTexture)
		{
			//texture not loaded
			printf("TEXTURE for bitmap '%s' not loaded!\n%s\n", m_image.c_str(), SDL_GetError());
		}
	}
}

void Sprite::DrawSelf()
{
	if (c_spriteSequence.size() > 1)
	{
		m_animationDelay++;
		if (m_animationDelay >= m_animationSpeed)
		{
			m_animationDelay = 0;
			m_spriteFrame++;
			if (m_spriteFrame >= c_spriteSequence.size()) m_spriteFrame = 0;
			std::string newImage = c_spriteSequence[m_spriteFrame];
			ChangeImage(newImage);
		}
	}

	//render the bitmap at the x/y coords
	if (p_bitmapTexture)
	{
		int x = p_parent->GetPosition(true).x;
		int y = p_parent->GetPosition(true).y;
		SDL_Rect destRect = { x, y, m_spriteWidth, m_spriteHeight };
		SDL_RenderCopyEx( //SDL_RenderCopy is the function used to render a texture to the rendering target. RenderCopyEx has extended features
			p_renderer, //the renderer to use
			p_bitmapTexture, //the texture to render
			NULL, //the source SDL_Rect structure or NULL for the entire texture
			&destRect, //the destination SDL_Rect structure or NULL for the entire rendering target, that being the whole screen
			0, NULL, //the angle and pivot points to rotate the image, NULL on the pivot point for centre
			p_parent->GetFlip()); //This parameter has a data type of SDL_RenderFlip, which can have values of SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL or SDL_FLIP_VERTICAL
	}
}

void Sprite::ChangeCollisionShape(int w, int h)
{
	if (w == -1 && h == -1)
	{
		m_useSpriteCollision = true;
		m_collisionHeight = m_spriteHeight;
		m_collisionWidth = m_spriteWidth;
		return;
	}
	m_useSpriteCollision = false;
	m_collisionWidth = abs(w);
	m_collisionHeight = abs(h);
}

std::string Sprite::GetSprite(int frame)
{
	if (frame > c_spriteSequence.size()) return "";
	else return c_spriteSequence[frame];
}
