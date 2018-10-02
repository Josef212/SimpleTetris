#include "Renderer.h"

#include "Window.h"


Renderer::Renderer()
{
	background = { 0, 0, 0, 255 };
}


Renderer::~Renderer()
{
}

void Renderer::Init(Window* window)
{
	Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

	this->window = window;

	renderer = SDL_CreateRenderer(window->GetWindow(), -1, flags);

	if (!renderer)
	{
		// TODO: Error
	}
	else
	{
		SDL_Surface* surface = window->GetSurface();

		camera.w = surface->w;
		camera.h = surface->h;
		camera.x = camera.y = 0;

		SDL_RenderGetViewport(renderer, &viewport);
	}
}

void Renderer::CleanUp()
{
	SDL_DestroyRenderer(renderer);
}

void Renderer::BeginFrame()
{
	SDL_RenderClear(renderer);
}

void Renderer::EndFrame()
{
	SDL_SetRenderDrawColor(renderer, background.r, background.g, background.b, background.a);
	SDL_RenderPresent(renderer);
}

void Renderer::DrawRect(SDL_Rect rect, SDL_Color color, bool filled, bool useCamera) const
{
	unsigned int scale = window->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_Rect r(rect);
	if (useCamera)
	{
		r.x = (int)(camera.x + rect.x * scale);
		r.y = (int)(camera.y + rect.y * scale);
		r.w *= scale;
		r.h *= scale;
	}

	if (filled) SDL_RenderFillRect(renderer, &r);
	else SDL_RenderDrawRect(renderer, &r);
}

void Renderer::DrawLine(int x0, int y0, int x1, int y1, SDL_Color & color, bool useCamera) const
{
	unsigned int scale = window->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	if (useCamera) SDL_RenderDrawLine(renderer, camera.x + x0 * scale, camera.y + y0 * scale,
		camera.x + x1 * scale, camera.y + y1 * scale);
	else SDL_RenderDrawLine(renderer, x0 * scale, y0 * scale, x1 * scale, y1 * scale);
}

void Renderer::DrawCircle(int x, int y, int radius, SDL_Color & color, bool useCamera)
{
	unsigned int scale = window->GetScale();

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	float factor = (float)M_PI / 180.0f;
	SDL_Point points[360];
	for (int i = 0; i < 360; ++i)
	{
		points[i].x = (int)(x + radius * cos(i * factor));
		points[i].y = (int)(y + radius * sin(i * factor));
	}

	SDL_RenderDrawPoints(renderer, points, 360);
}

void Renderer::SetViewport(SDL_Rect r)
{
	SDL_RenderSetViewport(renderer, &r);
}

void Renderer::ResetViewport()
{
	SDL_RenderSetViewport(renderer, &viewport);
}
