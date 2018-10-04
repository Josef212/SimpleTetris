#include "Textures.h"

#include "Renderer.h"

#include <SDL_image.h>
#include <iostream>


Textures::Textures()
{
}


Textures::~Textures()
{
}

void Textures::Init()
{
	int ret = IMG_Init(IMG_INIT_PNG);
	if (ret & IMG_INIT_PNG != IMG_INIT_PNG)
	{
		std::cout << "Could not init SDL_image. ERROR: " << SDL_GetError() << std::endl;
	}
}

void Textures::CleanUp()
{
	for (auto it : textures)
	{
		UnloadTexture(it, false);
	}

	IMG_Quit();
}

SDL_Texture * Textures::LoadTexture(std::string path, Renderer* renderer)
{
	SDL_Texture* ret = nullptr;

	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface)
	{
		ret = LoadTextureFromSurface(surface, renderer);

		SDL_FreeSurface(surface);
	}
	else
	{
		std::cout << "Could not load texture [" << path << "]. ERROR: " << SDL_GetError() << std::endl;
	}

	return ret;
}

void Textures::GetSize(SDL_Texture * texture, int & w, int & h)
{
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
}

SDL_Texture * Textures::LoadTextureFromSurface(SDL_Surface * surface, Renderer* renderer)
{
	SDL_Texture* ret = nullptr;

	ret = SDL_CreateTextureFromSurface(renderer->GetRenderer(), surface);

	if (ret) textures.push_back(ret);

	return ret;
}

bool Textures::UnloadTexture(SDL_Texture * texture, bool eraseFromList)
{
	auto it = std::find(textures.begin(), textures.end(), texture);

	if (it != textures.end())
	{
		if(eraseFromList) textures.erase(it);
		SDL_DestroyTexture(texture);
		return true;
	}

	return false;
}
