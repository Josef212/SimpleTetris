#include <iostream>
#include <SDL.h>

#include <Windows.h>

#include "Window.h"
#include "Renderer.h"
#include "Input.h"

// ----

int main(int argc, char** argv)
{

	Window w;
	Input i;
	Renderer r;

	w.Init();
	i.Init();
	r.Init(&w);

	while(!i.quitEvent)
	{
		i.BeginFrame();
		r.BeginFrame();


		r.DrawCircle(100, 100, 50, red);

		r.EndFrame();
	}

	r.CleanUp();
	i.CleanUp();
	w.CleanUp();

	return 0;
}