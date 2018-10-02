#ifndef __SCENE_H__
#define __SCENE_H__

class Renderer;
class Input;
class Window;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	void Init();
	void CleanUp();

	void BeginFrame();
	void Draw();

private:

};

#endif // !__SCENE_H__