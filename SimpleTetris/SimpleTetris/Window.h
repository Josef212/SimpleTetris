#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>

struct SDL_Window;
struct SDL_Surface;

class Window
{
public:
	Window();
	virtual ~Window();

	void Init();
	void CleanUp();

	SDL_Window* GetWindow()const { return window; }
	SDL_Surface* GetSurface()const { return surface; }

	std::string GetName()const { return name; }
	void SetName(const char* _name) { if (_name) name = name; }

	void GetSize(unsigned int& w, unsigned int& h);
	void SetSize(unsigned int& w, unsigned int& h);
	void SetWidth(unsigned int w);
	void SetHeight(unsigned int h);

	unsigned int GetScale()const { return scale; }
	void SetScale(unsigned int s) { scale = s; }

	bool Fullscreen()const { return fullscreen; }
	bool Borderless()const { return borderless; }
	bool Resizable()const { return resizable; }
	bool FullscreenWindow()const { return fullscreenWindow; }

	void SetFullscreen(bool set);
	void SetBorderless(bool set);
	void SetResizable(bool set);
	void SetFullscreenWindow(bool set);

private:
	SDL_Window* window = nullptr;
	SDL_Surface* surface = nullptr;

	std::string name = "Window";
	unsigned int width, height, scale;

	bool fullscreen, borderless, resizable, fullscreenWindow;

};

#endif // !__WINDOW_H__