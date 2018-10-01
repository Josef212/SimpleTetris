#include "Renderer.h"

#include "Window.h"


Renderer::Renderer()
{
	background = { 0, 0, 0, 1 };
}


Renderer::~Renderer()
{
}

void Renderer::Init(Window* window)
{
	Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

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

void Renderer::SetViewport(SDL_Rect r)
{
	SDL_RenderSetViewport(renderer, &r);
}

void Renderer::ResetViewport()
{
	SDL_RenderSetViewport(renderer, &viewport);
}
