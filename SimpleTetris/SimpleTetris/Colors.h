#ifndef __COLORS_H__
#define __COLORS_H__

#include <SDL.h>

enum Colors
{
	BLACK = 0,
	PINK = 1, 
	YELLOW = 2,
	RED = 3,
	CYAN = 4,
	ORANGE = 5,
	GREEN = 6,
	BLUE = 7,

	MAX_COL = 8
};

static SDL_Color white = { 255, 255, 255, 255 };
static SDL_Color black = { 0, 0, 0, 255 };
static SDL_Color red = { 255, 0, 0, 255 };
static SDL_Color green = { 0, 255, 0, 255 };
static SDL_Color blue = { 0, 0, 255, 255 };
static SDL_Color yellow = { 255, 255, 0, 255 };
static SDL_Color magenta = { 255, 0, 255, 255 };
static SDL_Color cyan = { 0, 255, 255, 255 };
static SDL_Color pink = { 204, 0, 102, 255 };
static SDL_Color orange = { 255, 128, 0, 255 };

static SDL_Color colors[MAX_COL] = 
{
	black,
	pink,
	yellow,
	red,
	cyan,
	orange,
	green,
	blue
};

#endif // __COLORS_H__