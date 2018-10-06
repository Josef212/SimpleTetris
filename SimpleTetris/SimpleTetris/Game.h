#ifndef __GAME_H__
#define __GAME_H__

#include "Board.h"
#include "Pieces.h"
#include <time.h>

class Renderer;

struct SDL_Texture;

#define WAIT_TIME 700		// Ms that the piece remains before movinf one block down

class Game
{
public:
	Game(Board* board, Pieces* pieces, int screenHeight, Renderer* renderer);
	virtual ~Game();

	void DrawScene();
	void CreateNewPiece();

	int posX, posY;			// Position of the piece it's falling
	int piece, rotation;	// Kind and rotation of the piece that is falling
	Colors pieceColor;

	SDL_Texture* sprites[MAX_COL];

	bool debug = false;

private:
	int screenHeight;
	int nextPosX, nextPosY;
	int nextPiece, nextRotation;
	Colors nextColor;

	Board* board;
	Pieces* pieces;
	Renderer* renderer;

	int GetRand(int a, int b);
	void InitGame();
	void DrawPiece(int x, int y, int piece, int rot, Colors color);
	void DrawBoard();
	void DrawColsLines();

};

#endif // !__GAME_H__