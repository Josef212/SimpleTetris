#ifndef __BOARD_H__
#define __BOARD_H__

#include "Pieces.h"
#include "Colors.h"

#define BOARD_LINE_WIDTH 6			// Width of the lines that delimit the board
#define BLOCK_SIZE 16				// Width & Height of each block of a piece
#define BOARD_POSITION 320			// Center position of the board from the left of the screen
#define BOARD_WIDTH 10				// Board blocks width
#define BOARD_HEIGHT 20				// Board blocks height
#define MIN_VERTICAL_MARGIN 20		// Minimum vertical margin for the board limit
#define MIN_HORITZONTAL_MARGIN 20	// Minimum horizontal margin for the board limit
#define PIECE_BLOCKS 5				// Number of horizontal and vertical blocks of a matrix piece

class Board
{
public:
	Board(Pieces* pieces, int screenHeight);
	virtual ~Board();

	int GetXPosInPixels(int pos);
	int GetYPosInPixels(int pos);
	bool IsFreeBlock(int x, int y);
	bool IsPossibleMovement(int x, int y, int piece, int rotation);
	void StorePiece(int x, int y, int piece, int rotation, Colors color);
	void DeletePossibleLines();
	bool IsGameOver();

	int GetBoardValue(int x, int y);

private:
	enum {POS_FREE, POS_FILLED};
	int board[BOARD_WIDTH][BOARD_HEIGHT];
	Pieces* pieces;
	int screenHeight;

	void InitBoard();
	void DeleteLine(int y);
};

#endif // !__BOARD_H__