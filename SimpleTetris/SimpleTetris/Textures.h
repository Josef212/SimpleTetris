#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include <string>
#include <list>

struct SDL_Texture;
struct SDL_Surface;
class Renderer;

class Textures
{
public:
	Textures();
	virtual ~Textures();

	void Init();
	void CleanUp();

	SDL_Texture* LoadTexture(std::string path, Renderer* renderer);
	void GetSize(SDL_Texture* texture, int& w, int& h);

private:
	SDL_Texture* LoadTextureFromSurface(SDL_Surface* surface, Renderer* renderer);
	bool UnloadTexture(SDL_Texture* texture, bool eraseFromList = true);

private:
	std::list<SDL_Texture*> textures;
};

#endif // __TEXTURES_H__