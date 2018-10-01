#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL.h>

class Window;

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void Init(Window* window);
	void CleanUp();

	void BeginFrame();
	void EndFrame();

	void DrawRect();
	void DrawLine();
	void DrawCircle();

	void SetViewport(SDL_Rect r);
	SDL_Rect GetViewport()const { return viewport; }
	void ResetViewport();

	SDL_Color GetBackground()const { return background; }
	void SetBackground(SDL_Color b) { background = b; }


public:
	SDL_Rect camera;

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect viewport;
	SDL_Color background;
};

#endif // !__RENDERER_H__