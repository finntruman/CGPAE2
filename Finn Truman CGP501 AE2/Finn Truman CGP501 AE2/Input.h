#pragma once
#include "SDL.h"

enum KEYS_LIST
{
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_JUMP, KEY_SHOOT, KEY_ESCAPE, KEYS_LIST_SIZE
};

class Input
{
private:
	//members
	SDL_Event m_event;
	int m_keysPressed[KEYS_LIST_SIZE];

	//methods
	int UpdateKey(int keyState, Uint32 keyboardEventType, Uint8 keyboardState);

public:
	Input();
	~Input();

	//methods
	void Update();
	bool KeyPressed(KEYS_LIST key); //returns true if the key has been pressed, so it will only return true on the first frame the key is held
	bool KeyHeld(KEYS_LIST key); //returns true if the key is pressed at all
	bool KeyUp(KEYS_LIST key); //only returns true if the key is released
	SDL_Event GetEvents() { return m_event; }
};