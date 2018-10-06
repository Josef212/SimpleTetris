#include "Game.h"

#include "Renderer.h"
#include <cstdlib>
#include <cstring>
#include <iostream>


Game::Game(Board* board, Pieces* pieces, int screenHeight, Renderer* renderer) : board(board), pieces(pieces), 
																screenHeight(screenHeight), renderer(renderer)
{
	memset(&sprites, 0, MAX_COL);
	InitGame();
}


Game::~Game()
{
}

void Game::DrawScene()
{
	DrawColsLines();
	DrawBoard();
	DrawPiece(posX, posY, piece, rotation, pieceColor);
	DrawPiece(nextPosX, nextPosY, nextPiece, nextRotation, nextColor);

	if(debug)
	{
		SDL_Rect r = { 0, 0, 16, 16 };
		for (int i = 0; i < MAX_COL; ++i)
		{
			renderer->Blit(sprites[i], r.x, r.y);
			r.x += r.w;
		}
	}
}

void Game::CreateNewPiece()
{
	piece = nextPiece;
	rotation = nextRotation;
	posX = (BOARD_WIDTH / 2) + pieces->GetXInitialPos(piece, rotation);
	posY = pieces->GetYInitialPos(piece, rotation);
	pieceColor = nextColor;

	nextPiece = GetRand(0, 6);
	nextRotation = GetRand(0, 3);
	nextColor = (Colors)GetRand(1, MAX_COL - 1);
}

int Game::GetRand(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

void Game::InitGame()
{
	srand((unsigned int)time(NULL));

	piece = GetRand(0, 6);
	rotation = GetRand(0, 3);
	posX = (BOARD_WIDTH / 2) + pieces->GetXInitialPos(piece, rotation);
	posY = pieces->GetYInitialPos(piece, rotation);
	pieceColor = (Colors)GetRand(1, MAX_COL - 1);

	nextPiece = GetRand(0, 6);
	nextRotation = GetRand(0, 3);
	nextPosX = BOARD_WIDTH + 5;
	nextPosY = 5;
	nextColor = (Colors)GetRand(1, MAX_COL - 1);
}

void Game::DrawPiece(int x, int y, int piece, int rot, Colors color)
{
	SDL_Color _color;
	SDL_Texture* texture = nullptr;

	int pixelX = board->GetXPosInPixels(x);
	int pixelY = board->GetYPosInPixels(y);

	for (int i = 0; i < PIECE_BLOCKS; ++i)
	{
		for (int j = 0; j < PIECE_BLOCKS; ++j)
		{
			if (debug)
			{
				switch (pieces->GetBlockType(piece, rot, j, i))
				{
				case 1: _color = green; break;
				case 2: _color = blue; break;
				}

				//_color = colors[color];
			}
			else
			{
				texture = sprites[color];
			}
			

			if (pieces->GetBlockType(piece, rot, j, i) != 0)
			{
				if (debug)
				{
					renderer->DrawRect({ pixelX + i * BLOCK_SIZE, pixelY + j * BLOCK_SIZE,
					   BLOCK_SIZE, BLOCK_SIZE },
						_color);
				}
				else
				{
					renderer->Blit(texture, pixelX + i * BLOCK_SIZE, pixelY + j * BLOCK_SIZE);
				}
			}
		}
	}
}

void Game::DrawBoard()
{
	int boardPixelsHeight = BLOCK_SIZE * BOARD_HEIGHT;

	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = screenHeight - boardPixelsHeight;

	

	renderer->DrawRect({ mX1 - BOARD_LINE_WIDTH, mY, BOARD_LINE_WIDTH, boardPixelsHeight }, blue);
	
	renderer->DrawRect({ mX2, mY, BOARD_LINE_WIDTH, boardPixelsHeight }, blue);

	mX1 += 1;
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			if (!board->IsFreeBlock(i, j))
			{
				if(debug)
				{
					SDL_Color col = colors[board->GetBoardValue(i, j)];
					renderer->DrawRect({ mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE,
						BLOCK_SIZE, BLOCK_SIZE },
						col);
				}
				else
				{
					renderer->Blit(sprites[board->GetBoardValue(i, j)], mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE);
				}
				
			}
		}
	}
}

void Game::DrawColsLines()
{
	SDL_Color color = white;
	color.a = 160;

	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int boardPixelsHeight = BLOCK_SIZE * BOARD_HEIGHT;

	for(int c = 1; c < BOARD_WIDTH; ++c)
	{
		int x0 = mX1 + c * BLOCK_SIZE;
		int y0 = screenHeight - boardPixelsHeight;

		int x1 = x0;
		int y1 = screenHeight;

		renderer->DrawLine(x0, y0, x1, y1, color, false);
	}
}
