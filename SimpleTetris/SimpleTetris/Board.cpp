#include "Board.h"



Board::Board(Pieces* pieces, int screenHeight) : screenHeight(screenHeight)
{
}


Board::~Board()
{
}

int Board::GetXPosInPixels(int pos)
{
	return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pos * BLOCK_SIZE));
}

int Board::GetYPosInPixels(int pos)
{
	return ((screenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pos * BLOCK_SIZE));
}

bool Board::IsFreeBlock(int x, int y)
{
	return board[x][y] == POS_FREE;
}

bool Board::IsPossibleMovement(int x, int y, int piece, int rotation)
{
	for (int i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; ++i1, ++i2)
	{
		for (int j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; ++j1, ++j2)
		{
			if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1)
			{
				if (pieces->GetBlockType(piece, rotation, j2, i2) != 0)
					return false;
			}

			if (j1 >= 0)
			{
				if ((pieces->GetBlockType(piece, rotation, j2, i2) != 0)
					&& (!IsFreeBlock(i1, j1)))
				{
					return false;
				}
			}
		}
	}

	return true;
}

void Board::StorePiece(int x, int y, int piece, int rotation, Colors color)
{
	for (int i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; ++i1, ++i2)
	{
		for (int j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; ++j1, ++j2)
		{
			if (pieces->GetBlockType(piece, rotation, j2, i2) != 0)
				board[i1][j1] = (color > 0 && color < MAX_COL ? color : POS_FILLED);
		}
	}
}

void Board::DeletePossibleLines()
{
	for (int j = 0; j < BOARD_HEIGHT; ++j)
	{
		int i = 0; 
		while (i < BOARD_WIDTH)
		{
			if (board[i][j] == POS_FREE) break;
			++i;
		}

		if (i == BOARD_WIDTH) DeleteLine(j);
	}
}

bool Board::IsGameOver()
{
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		if (board[i][0] != POS_FREE) return true;
	}

	return false;
}

int Board::GetBoardValue(int x, int y)
{
	if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT)
		return board[x][y];
	return 0;
}

void Board::InitBoard()
{
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			board[i][j] = POS_FREE;
		}
	}
}

void Board::DeleteLine(int y)
{
	for (int j = y; j > 0; --j)
	{
		for (int i = 0; i < BOARD_WIDTH; ++i)
		{
			board[i][j] = board[i][j - 1];
		}
	}
}
