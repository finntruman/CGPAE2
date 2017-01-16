#include "Input.h"

//these are the four states a key can be in:
#define INACTIVE 0 //the key isn't doing anything
#define PRESSED 1 //the key has been pressed this frame
#define DOWN 2 //the key was already pressed since at least the previous frame, i.e. its being held down
#define RELEASED 3 //the key has been released this frame

Input::Input()
{
	for (int i = 0; i < KEYS_LIST_SIZE; i++)
	{
		m_keysPressed[i] = INACTIVE; //go through all of the keys and set them to inactive
	}
}

Input::~Input()
{
}

void Input::Update()
{
	//make released keys inactive
	for (int i = 0; i < KEYS_LIST_SIZE; i++) //sets any keys that were RELEASED on the previous frame to INACTIVE
	{
		if (m_keysPressed[i] == RELEASED) m_keysPressed[i] = INACTIVE;
	}

	//loop through all the events in the event list
	while (SDL_PollEvent(&m_event) != NULL)
	{
		if (m_event.type == SDL_KEYUP || m_event.type == SDL_KEYDOWN)
		{
			//cache the code of key we pressed for easier debugging
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			switch (keyPressed)
			{
			case SDLK_w:
				m_keysPressed[KEY_UP] = UpdateKey(m_keysPressed[KEY_UP], m_event.type, m_event.key.state);
				//m_keysPressed[KEY_UP] = UpdateKey(m_keysPressed[KEY_UP]);
				break;

			case SDLK_s:
				m_keysPressed[KEY_DOWN] = UpdateKey(m_keysPressed[KEY_DOWN], m_event.type, m_event.key.state);
				//m_keysPressed[KEY_DOWN] = UpdateKey(m_keysPressed[KEY_DOWN]);
				break;

			case SDLK_a:
				m_keysPressed[KEY_LEFT] = UpdateKey(m_keysPressed[KEY_LEFT], m_event.type, m_event.key.state);
				//m_keysPressed[KEY_LEFT] = UpdateKey(m_keysPressed[KEY_LEFT]);
				break;

			case SDLK_d:
				m_keysPressed[KEY_RIGHT] = UpdateKey(m_keysPressed[KEY_RIGHT], m_event.type, m_event.key.state);
				//m_keysPressed[KEY_RIGHT] = UpdateKey(m_keysPressed[KEY_RIGHT]);
				break;

			case SDLK_SPACE:
				m_keysPressed[KEY_SHOOT] = UpdateKey(m_keysPressed[KEY_SHOOT], m_event.type, m_event.key.state);
				//m_keysPressed[KEY_SHOOT] = UpdateKey(m_keysPressed[KEY_SHOOT]);
				break;

			case SDLK_ESCAPE:
				m_keysPressed[KEY_ESCAPE] = UpdateKey(m_keysPressed[KEY_ESCAPE], m_event.type, m_event.key.state);
				//m_keysPressed[KEY_ESCAPE] = UpdateKey(m_keysPressed[KEY_ESCAPE]);
				break;
			}
		}
	}
}

int Input::UpdateKey(int keyState, Uint32 keyboardEventType, Uint8 keyboardState)
{
	/*if (keyboardEventType == SDL_KEYDOWN)
	{
		if (keyboardState == SDL_PRESSED) return PRESSED;
		else return DOWN;
	}
	else if (keyboardEventType == SDL_KEYUP) return RELEASED;
	return INACTIVE;*/

	if (keyboardEventType == SDL_KEYDOWN) //if the SDL event is a KeyDown event...
	{
		if (keyState == INACTIVE) return PRESSED; //if the key is INACTIVE, then it must have just been pressed this frame, so set it to PRESSED
		else if (keyState == PRESSED || keyState == DOWN) return DOWN; //else if the key is currently PRESSED or DOWN, then it is being held, so set/keep it to DOWN
	}
	else if (keyboardEventType == SDL_KEYUP) return RELEASED; //but if the SDL event is a KeyUp event, regardless of what the previous state was, set it to RELEASED
	return INACTIVE; //returns INACTIVE if the event type is for some reason not KeyDown or KeyUp
}

bool Input::KeyPressed(KEYS_LIST key)
{
	return (m_keysPressed[key] == PRESSED);
}

bool Input::KeyHeld(KEYS_LIST key)
{
	return (m_keysPressed[key] == PRESSED || m_keysPressed[key] == DOWN);
}

bool Input::KeyUp(KEYS_LIST key)
{
	return (m_keysPressed[key] == RELEASED);
}