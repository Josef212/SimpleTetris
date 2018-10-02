#include "Input.h"

#include <SDL.h>
#include <cstring>

#define MAX_KEYS 300

Input::Input() : mouseX(0), mouseY(0), wheel(0), mouseMotionX(0), mouseMotionY(0)
{
	keyboard = new KeyState[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KeyState) * MAX_KEYS);
	memset(mouse, KEY_IDLE, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}


Input::~Input()
{
	if (keyboard) delete[] keyboard;
}

void Input::Init()
{
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		// TODO: Error
	}
}

void Input::CleanUp()
{
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void Input::BeginFrame()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(nullptr);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouseX, &mouseY);

	wheel = mouseMotionX = mouseMotionY = 0;

	for (int i = 0; i < NUM_MOUSE_BUTTONS; ++i)
	{
		if (buttons & SDL_BUTTON(i))
		{
			if (mouse[i] == KEY_IDLE) mouse[i] = KEY_DOWN;
			else mouse[i] = KEY_REPEAT;
		}
		else
		{
			if (mouse[i] == KEY_REPEAT || mouse[i] == KEY_DOWN) mouse[i] = KEY_DOWN;
			else mouse[i] = KEY_IDLE;
		}
	}

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_MOUSEWHEEL:
			wheel = e.wheel.y;
			break;

		case SDL_MOUSEMOTION:
			mouseX = e.motion.x;
			mouseY = e.motion.y;
			mouseMotionX = e.motion.xrel;
			mouseMotionY = e.motion.yrel;
			break;

		case SDL_QUIT:
			quitEvent = true;
			break;



		default:
			break;
		}
	}

	SDL_PollEvent(&e);
}
