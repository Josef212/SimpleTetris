#include <iostream>
#include <SDL.h>

#include <Windows.h>

#include "Window.h"
#include "Renderer.h"

// ----

int main(int argc, char** argv)
{

	Window w;
	Renderer r;

	w.Init();
	r.Init(&w);

	for (int i = 0; i < 1000; ++i)
	{
		r.BeginFrame();

		

		Sleep(15);

		r.EndFrame();
	}

	r.CleanUp();
	w.CleanUp();

	return 0;
}