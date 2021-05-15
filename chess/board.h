#pragma once
#include <conio.h>
#include <iostream>
#include <iomanip>
#define BOARDLEN 8
using namespace std;

struct Position {
public:
	int x; // X, y Coordinate.
	int y;
};

enum mynum
{
	null = 0,
	King = 1,
	Queen = 2,
	Rook = 3,
	Bishop = 4,
	Knight = 5,
	Pawn = 6,
};

class piece
{
public:
	piece() :pieceId(null), camp(-999), moved(0) {}
	piece(int id, int c) :pieceId(id), camp(c), moved(0) {}
	friend ostream& operator<<(ostream& str, piece p)
	{
		str << p.pieceId;
		return str;
	}
	int pieceId;
	int camp;
	bool moved = 0;

};


class Board
{
public:
	//declare chess board.
	piece board[BOARDLEN][BOARDLEN];
	void print();
	void print(Position);
	Board();
protected:
private:
};
Board::Board()
{
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			board[i][j] = piece();
		}
	}
	board[0][0] = piece(Rook, 1);
	board[0][1] = piece(Knight, 1);
	board[0][2] = piece(Bishop, 1);
	board[0][3] = piece(Queen, 1);
	board[0][4] = piece(King, 1);
	board[0][5] = piece(Bishop, 1);
	board[0][6] = piece(Knight, 1);
	board[0][7] = piece(Rook, 1);

	board[7][0] = piece(Rook, 0);
	board[7][1] = piece(Knight, 0);
	board[7][2] = piece(Bishop, 0);
	board[7][3] = piece(Queen, 0);
	board[7][4] = piece(King, 0);
	board[7][5] = piece(Bishop, 0);
	board[7][6] = piece(Knight, 0);
	board[7][7] = piece(Rook, 0);

	for (int i = 0; i < BOARDLEN; i++)
	{
		board[1][i] = piece(Pawn, 1);
		board[6][i] = piece(Pawn, 0);
	}
}


void Board::print()
{
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			cout << setw(2) << board[i][j];
		}
		cout << endl;
	}
}
void Board::print(Position p)
{
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			if(i == p.x && j == p.y)
				cout << setw(2) << "X";
			else
				cout << setw(2) << board[i][j];
		}
		cout << endl;
	}
}
