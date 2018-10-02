#ifndef __INPUT_H__
#define __INPUT_H__

#include <SDL_scancode.h>
#include <SDL_mouse.h>

#define NUM_MOUSE_BUTTONS 5

typedef enum {
	KEY_IDLE,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
} KeyState;

class Input
{
public:
	Input();
	virtual ~Input();

	void Init();
	void CleanUp();

	void BeginFrame();

	KeyState GetKey(int id) const { return keyboard[id]; }
	KeyState GetMouseButton(int id) const { return mouse[id]; }

	bool GetKeyDown(int id) const { return keyboard[id] == KEY_DOWN; }
	bool GetKeyUp(int id) const { return keyboard[id] == KEY_UP; }
	bool GetKeyRepeat(int id) const { return keyboard[id] == KEY_REPEAT; }

	int GetMouseX() const { return mouseX; }
	int GetMouseY() const { return mouseY; }
	int GetMouseMotionX() const { return mouseMotionX; }
	int GetMouseMotionY() const { return mouseMotionY; }

	bool quitEvent = false;

private:
	KeyState* keyboard = nullptr;
	KeyState mouse[NUM_MOUSE_BUTTONS];

	int mouseX, mouseY, wheel;
	int mouseMotionX, mouseMotionY;
};

#endif // !__INPUT_H__