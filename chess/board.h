#pragma once
#include <iostream>
#include <iomanip>
#define BOARDLEN 8
using namespace std;

struct Position {
	int x; // X, y Coordinate.
	int y;
};

class Board
{
public:
	//piece codename.
	enum mynum
	{
		empty = 0,
		//white side.
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
		piece() :pieceId(empty) {}
		piece(int id, int c) :pieceId(id), camp(c) {}
		void move()
		{
			switch (pieceId)
			{
			default:
				break;
			}
		}
		friend ostream& operator<<(ostream& str, piece p)
		{
			str << p.pieceId;
			return str;
		}
		int pieceId;
		int camp;

	};
	//declare chess board.
	piece board[BOARDLEN][BOARDLEN];
	Position startPos;
	Position assignPos;


	void moveKing(Position, Position);
	void moveQueen(Position, Position);
	void moveRook(Position, Position);
	void moveBishop(Position, Position);
	void moveKnight(Position, Position);
	void movePawn(Position, Position);
	void print();


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
			board[i][j] = piece(empty, 0);
		}
	}
	board[0][0] = piece(Rook, -1);
	board[0][1] = piece(Knight, -1);
	board[0][2] = piece(Bishop, -1);
	board[0][3] = piece(Queen, -1);
	board[0][4] = piece(King, -1);
	board[0][5] = piece(Bishop, -1);
	board[0][6] = piece(Knight, -1);
	board[0][7] = piece(Rook, -1);

	board[7][0] = piece(Rook, 1);
	board[7][1] = piece(Knight, 1);
	board[7][2] = piece(Bishop, 1);
	board[7][3] = piece(Queen, 1);
	board[7][4] = piece(King, 1);
	board[7][5] = piece(Bishop, 1);
	board[7][6] = piece(Knight, 1);
	board[7][7] = piece(Rook, 1);

	for (int i = 0; i < BOARDLEN; i++)
	{
		board[1][i] = piece(Pawn, -1);
		board[6][i] = piece(Pawn, 1);
	}
}



void Board::moveKing(Position startPos, Position assignPos)
{
	//四周八格
	if (abs(assignPos.x - startPos.x) == 1)
	{
		if (abs(assignPos.y - startPos.y) == 1)
		{
			board[assignPos.x][assignPos.y] = board[startPos.x][startPos.y];
		}
		else return;
	}
	else return;
}

void Board::moveQueen(Position startPos, Position assignPos)
{
	int queenX = startPos.x;
	int queenY = startPos.y;
	int thatX = assignPos.x;
	int thatY = assignPos.y;


	if (queenX != thatX || queenY != thatY) //不是同位置
	{
		//同X
		if (queenX == thatX)
		{
			board[thatX][thatY] = board[queenX][queenY];
		}
		else
		{
			if (queenY == thatY) //同Y
			{
				board[thatX][thatY] = board[queenX][queenY];
			}
			else
			{
				if (abs(queenX - thatX) == abs(queenY - thatY)) //斜向
				{
					board[thatX][thatY] = board[queenX][queenY];
				}
				else
				{
					return;
				}
			}

		}

	}
}
void Board::moveRook(Position startPos, Position assignPos)
{
	int rookX = startPos.x;
	int rookY = startPos.x;
	int thatX = assignPos.x;
	int thatY = assignPos.y;

	if (rookX != thatX || rookY != thatY) //不是同位置
	{

		if (rookX == thatX) //同X
		{
			board[thatX][thatY] = board[rookX][rookY];
		}
		else
		{
			if (rookY == thatY) //同Y
			{
				board[thatX][thatY] = board[rookX][rookY];
			}
			else
			{
				return;
			}
		}

	}
}

void Board::moveBishop(Position startPos, Position assignPos)
{
	int bishopX = startPos.x;
	int bishopY = startPos.y;
	int thatX = assignPos.x;
	int thatY = assignPos.y;

	if (abs(bishopX - thatX) == abs(bishopY - thatY)) //斜向
	{
		board[thatX][thatY] = board[bishopX][bishopY];
	}
	else
	{
		return;
	}

}

void Board::moveKnight(Position startPos, Position assignPos)
{
	int knightX = startPos.x;
	int knightY = startPos.y;
	int thatX = assignPos.x;
	int thatY = assignPos.y;

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2)) //日字
	{
		board[thatX][thatY] = board[knightX][knightY];
	}
	else
	{
		return;
	}

}

void Board::movePawn(Position startPos, Position assignPos)
{
	int pawnX = startPos.x;
	int pawnY = startPos.y;
	int thatX = assignPos.x;
	int thatY = assignPos.y;

	//還想不到怎麼搞第一步2格
	//跟要判斷黑白兩方
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