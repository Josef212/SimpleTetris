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

	void DrawRect(SDL_Rect& rect, SDL_Color& color, bool filled = true, bool useCamera = true)const;
	void DrawLine(int x0, int y0, int x1, int y1, SDL_Color& color, bool useCamera = true)const;
	void DrawCircle(int x, int y, int radius, SDL_Color& color, bool useCamera = true);

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
	Window* window = nullptr;
};

#endif // !__RENDERER_H__