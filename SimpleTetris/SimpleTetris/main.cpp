/**
	A simple tetris game made following the tutorial: http://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/
*/

#include <iostream>
#include <SDL.h>

#include "Window.h"
#include "Renderer.h"
#include "Input.h"
#include "Scene.h"

// ----

int main(int argc, char** argv)
{

	Window w;
	Input i;
	Renderer r;

	Scene s;

	w.Init();
	i.Init();
	r.Init(&w);

	s.Init(&w, &r);

	while(!i.quitEvent)
	{
		i.BeginFrame();
		r.BeginFrame();

		s.BeginFrame(&w, &i);

		s.Draw();

		r.EndFrame();
	}

	s.CleanUp();

	r.CleanUp();
	i.CleanUp();
	w.CleanUp();

	system("PAUSE");

	return 0;
}