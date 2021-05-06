#pragma once
#include <iostream>

#define BOARDLEN 8
using namespace std;

struct Position {
	int x; // X, y Coordinate.
	int y;
};

class Board
{
public:
	//declare chess board.
	int board[BOARDLEN][BOARDLEN] = { 0 };

	Position startPos;
	Position assignPos;

	//piece codename.
	enum piece
	{
		empty = 0,

		//white side.
		WKing = 1,
		WQueen = 2,
		WRook = 3,
		WBishop = 4,
		WKnight = 5,
		WPawn = 6,

		//black side.
		BKing = -1,
		BQueen = -2,
		BRook = -3,
		BBishop = -4,
		BKnight = -5,
		BPawn = -6,
	};

	void moveKing(Position, Position);
	void moveQueen(Position, Position);
	void moveRook(Position, Position);
	void moveBishop(Position, Position);
	void moveKnight(Position, Position);
	void movePawn(Position, Position);


	

	Board();

protected:
private:
};

Board::Board()
{
	board[0][0] = BRook;
	board[0][1] = BKnight;
	board[0][2] = BBishop;
	board[0][3] = BQueen;
	board[0][4] = BKing;
	board[0][5] = BBishop;
	board[0][6] = BKnight;
	board[0][7] = BRook;

	board[7][0] = WRook;
	board[7][1] = WKnight;
	board[7][2] = WBishop;
	board[7][3] = WQueen;
	board[7][4] = WKing;
	board[7][5] = WBishop;
	board[7][6] = WKnight;
	board[7][7] = WRook;

	for (int i = 0; i < BOARDLEN; i++)
	{
		board[1][i] = BPawn;
		board[6][i] = WPawn;
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
