#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL.h>
#include <climits>

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

	void DrawRect(SDL_Rect rect, SDL_Color color, bool filled = true, bool useCamera = false)const;
	void DrawLine(int x0, int y0, int x1, int y1, SDL_Color& color, bool useCamera = true)const;
	void DrawCircle(int x, int y, int radius, SDL_Color& color, bool useCamera = true);

	void Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section = NULL, double angle = 0, int pivotX = INT_MAX, int pivotY = INT_MAX);

	void SetViewport(SDL_Rect r);
	SDL_Rect GetViewport()const { return viewport; }
	void ResetViewport();

	SDL_Color GetBackground()const { return background; }
	void SetBackground(SDL_Color b) { background = b; }

	SDL_Renderer* GetRenderer()const { return renderer; }


public:
	SDL_Rect camera;

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect viewport;
	SDL_Color background;
	Window* window = nullptr;
};

#endif // !__RENDERER_H__