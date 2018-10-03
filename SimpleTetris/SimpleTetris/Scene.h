#ifndef __SCENE_H__
#define __SCENE_H__

class Renderer;
class Input;
class Window;
class Textures;
class Pieces;
class Board;
class Game;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	void Init(Window* w, Renderer* r, Textures* t);
	void CleanUp();

	void BeginFrame(Window* w, Input* i);
	void Draw();

private:

	Pieces* pieces;
	Board* board;
	Game* game;

	unsigned long time1 = 0;

};

#endif // !__SCENE_H__