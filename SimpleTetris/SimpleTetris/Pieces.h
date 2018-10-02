#ifndef __PIECES_H__
#define __PIECES_H__

class Pieces
{
public:
	Pieces();
	~Pieces();

	int GetBlockType(int piece, int rotation, int x, int y);
	int GetXInitialPos(int piece, int rotation);
	int GetYInitialPos(int piece, int rotation);
	
};

#endif // !__PIECES_H__