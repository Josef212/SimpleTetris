#include "Window.h"

#include <SDL.h>

#define DEFAULT_WIDTH 1080
#define DEFAULT_HEIGHT 720
#define DEFAULT_SCALE 1

#define FULLSCREEN false
#define BORDERLESS false
#define RESIZABLE false
#define FULLSCREEN_WINDOW false

Window::Window() : width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT), scale(DEFAULT_SCALE), 
					fullscreen(FULLSCREEN), borderless(BORDERLESS), resizable(RESIZABLE), 
					fullscreenWindow(FULLSCREEN_WINDOW)
{
}


Window::~Window()
{
}

void Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		// ERROR
	}
	else
	{
		Uint32 flags = SDL_WINDOW_SHOWN;

		if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN;
		if (borderless) flags |= SDL_WINDOW_BORDERLESS;
		if (resizable) flags |= SDL_WINDOW_RESIZABLE;
		if (fullscreenWindow) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

		window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if (window) surface = SDL_GetWindowSurface(window);

		if (surface)
		{
			width = surface->w;
			height = surface->h;
		}

	}
}

void Window::CleanUp()
{
	if (window)
		SDL_DestroyWindow(window);
	
	SDL_Quit();
}

void Window::GetSize(unsigned int & w, unsigned int & h)
{
	w = width;
	h = height;
}

void Window::SetSize(unsigned int & w, unsigned int & h)
{
	width = w;
	height = h;
	// TODO: Resize
}

void Window::SetWidth(unsigned int w)
{
	width = w;
	// TODO: Resize
}

void Window::SetHeight(unsigned int h)
{
	height = h;
	// TODO: Resize
}

void Window::SetFullscreen(bool set)
{
	fullscreen = set;
	// TODO:
}

void Window::SetBorderless(bool set)
{
	borderless = set;
	// TODO: 
}

void Window::SetResizable(bool set)
{
	resizable = set;
	// TODO: 
}

void Window::SetFullscreenWindow(bool set)
{
	fullscreenWindow = set;
	// TODO: 
}
