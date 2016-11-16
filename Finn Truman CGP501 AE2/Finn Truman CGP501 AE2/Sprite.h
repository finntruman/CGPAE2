#pragma once
#include <string>
#include <vector>
#include "SDL.h"

class Actor;

class Sprite
{
private:
	SDL_Surface* p_bitmapSurface;
	SDL_Texture* p_bitmapTexture;
	SDL_Renderer* p_renderer;

	Actor* p_parent; //the sprite needs a pointer to its parent to get its position
	std::vector<std::string> c_spriteSequence; //the vector of strings is the sequence of images to cycle through to create animation

	/*
		animationDelay increases by 1 every frame until it equates to animationSpeed, at which point Delay is reset to 0 and the next frame of the sprite animation is drawn.
		This allows for animations with fewer frames to be animated slower
	*/
	int m_spriteWidth, m_spriteHeight;
	int m_collisionWidth, m_collisionHeight;
	bool m_useSpriteCollision;
	int m_spriteFrame, m_animationSpeed, m_animationDelay;
	std::string m_image; //the directory of the image to draw

public:
	Sprite(SDL_Renderer &renderer, Actor &parent, std::vector<std::string> sprites);
	~Sprite();

	void ChangeSprite(std::string sprite);
	void ChangeSprite(std::vector<std::string> sprites); //ChangeSprite does something slightly differently depending if a single image or an entirely new sprite sequence is passed
	void ChangeImage(std::string sprite); //ChangeImage is what actually changes the image currently being drawn
	void ChangeCollisionShape(int w, int h); //changes the collision shape of the character, setting both to -1 will use the sprite dimensions. if one is set to -1 and the other isn't, the -1 will be rounded to 1
	void DrawSelf(); //DrawSelf manages the animation, this is what increases animationDelay and compares it to animationSpeed, and calls ChangeImage to draw a new image when the next animation frame is needed
	std::string GetSprite(int frame = 0); //this returns the directory of the frame of the sprite equal to the parameter, if no parameter is given it defaults to 0
	
	void SetSpeed(int speed) { m_animationSpeed = speed; } //sets the speed of the animation, which is a bit counter intuitive because the bigger animationSpeed is the slower the animation.
	int GetSpriteHeight() { return m_spriteHeight; } //simple Get functions for the sprite height and width
	int GetSpriteWidth() { return m_spriteWidth; }
	int GetCollisionHeight() { return m_collisionHeight; }
	int GetCollisionWidth() { return m_collisionWidth; }
};

