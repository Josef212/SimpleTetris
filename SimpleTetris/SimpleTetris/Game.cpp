#include "Game.h"

#include "Renderer.h"
#include <cstdlib>


Game::Game(Board* board, Pieces* pieces, int screenHeight, Renderer* renderer) : board(board), pieces(pieces), 
																screenHeight(screenHeight), renderer(renderer)
{
	InitGame();
}


Game::~Game()
{
}

void Game::DrawScene()
{
	DrawBoard();
	DrawPiece(posX, posY, piece, rotation);
	DrawPiece(nextPosX, nextPosY, nextPiece, nextRotation);
}

void Game::CreateNewPiece()
{
	piece = nextPiece;
	rotation = nextRotation;
	posX = (BOARD_WIDTH / 2) + pieces->GetXInitialPos(piece, rotation);
	posY = pieces->GetYInitialPos(piece, rotation);

	nextPiece = GetRand(0, 6);
	nextRotation = GetRand(0, 3);
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

	nextPiece = GetRand(0, 6);
	nextRotation = GetRand(0, 3);
	nextPosX = BOARD_WIDTH + 5;
	nextPosY = 5;
}

void Game::DrawPiece(int x, int y, int piece, int rot)
{
	SDL_Color color;

	int pixelX = board->GetXPosInPixels(x);
	int pixelY = board->GetYPosInPixels(y);

	for (int i = 0; i < PIECE_BLOCKS; ++i)
	{
		for (int j = 0; j < PIECE_BLOCKS; ++j)
		{
			switch (pieces->GetBlockType(piece, rot, j, i))
			{
				case 1: color = green; break;
				case 2: color = blue; break;
			}

			if (pieces->GetBlockType(piece, rot, j, i) != 0)
			{
				if (debug)
				{
					renderer->DrawRect({ pixelX + i * BLOCK_SIZE, pixelY + j * BLOCK_SIZE,
					   BLOCK_SIZE, BLOCK_SIZE },
						color);
				}
				else
				{
					renderer->Blit(pieceSprite, pixelX + i * BLOCK_SIZE, pixelY + j * BLOCK_SIZE);
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
				renderer->DrawRect({ mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE,
									BLOCK_SIZE, BLOCK_SIZE },
									red);
			}
		}
	}
}
