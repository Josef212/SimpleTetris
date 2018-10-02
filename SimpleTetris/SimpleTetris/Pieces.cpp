#include "Pieces.h"
#include "PiecesInfo.h"

Pieces::Pieces()
{
}

Pieces::~Pieces()
{
}

int Pieces::GetBlockType(int piece, int rotation, int x, int y)
{
	return pieces[piece][rotation][x][y];
}

int Pieces::GetXInitialPos(int piece, int rotation)
{
	return piecesInitialPosition[piece][rotation][0];
}

int Pieces::GetYInitialPos(int piece, int rotation)
{
	return piecesInitialPosition[piece][rotation][1];
}
