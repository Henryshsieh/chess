#pragma once
#include <conio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#define BOARDLEN 8
using namespace std;

struct Position {
public:
	Position():x(0),y(0){}
	Position(int _x, int _y):x(_x), y(_y){}
	int x; // X, y Coordinate.
	int y;
};

enum mynum
{
	null = 0,
	KING = 1,
	QUEEN = 2,
	ROOK = 3,
	BISHOP = 4,
	KNIGHT = 5,
	PAWN = 6,
};

class piece
{
public:
	piece() :pieceId(null), camp(-999), pieceIndex(0), moved(0) {}
	piece(int id, int inx, int c, int x, int y) :pieceId(id), pieceIndex(inx), camp(c), moved(0) 
	{
		_position.x = x;
		_position.y = y;
	}
	friend ostream& operator<<(ostream& str, piece p)
	{
		if (p.pieceId == 0)
			str << " ";
		else
			str << p.pieceId;
		return str;
	}
	int pieceId; // types of chess pieces
	int pieceIndex; // to distinguish pieces of same type
	int camp; // black side or white side; represented by 1 and 0
	bool moved = 0;
	Position _position;
	vector <Position> attack;
	vector <Position> availablemove;

};
class Board
{
public:
	//declare chess board.
	piece board[BOARDLEN][BOARDLEN];
	void save();
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
	board[0][0] = piece(ROOK, 0, 1, 0, 0);
	board[0][1] = piece(KNIGHT, 0, 1, 0, 1);
	board[0][2] = piece(BISHOP, 0, 1, 0, 2);
	board[0][3] = piece(QUEEN, 0, 1, 0, 3);
	board[0][4] = piece(KING, 0, 1, 0, 4);
	board[0][5] = piece(BISHOP, 1, 1, 0, 5);
	board[0][6] = piece(KNIGHT, 1, 1, 0, 6);
	board[0][7] = piece(ROOK, 1, 1, 0, 7);

	board[7][0] = piece(ROOK, 0, 0, 7, 0);
	board[7][1] = piece(KNIGHT, 0, 0, 7, 1);
	board[7][2] = piece(BISHOP, 0, 0, 7, 2);
	board[7][3] = piece(QUEEN, 0, 0, 7, 3);
	board[7][4] = piece(KING, 0, 0, 7, 4);
	board[7][5] = piece(BISHOP, 1, 0, 7, 5);
	board[7][6] = piece(KNIGHT, 1, 0, 7, 6);
	board[7][7] = piece(ROOK, 1, 0, 7, 7);

	for (int i = 0; i < BOARDLEN; i++)
	{
		board[1][i] = piece(PAWN, i, 1, 1, i);
		board[6][i] = piece(PAWN, i, 0, 6, i);
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
void Board::save()
{
	fstream str;
	str.open("./file.txt", std::ios_base::app | std::ios_base::in);

	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			str << " " << board[i][j];
		}
		str << endl;
	}
}
void Board::print(Position p)
{
	piece temp[BOARDLEN][BOARDLEN];
	vector<Position> vec;
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			temp[i][j] = board[i][j];
			if (i == p.x && j == p.y)
			{
				vec.resize(board[i][j].availablemove.size());
				vec.assign(board[i][j].availablemove.begin(), board[i][j].availablemove.end());
			}
		}
	}

	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			int check = 0;
			if (i == p.x && j == p.y)
			{
				cout << setw(2) << "X";
				check = 1;
			}
			else if(vec.size())
				for (auto element:vec)
				{
					if (i == element.x && j == element.y)
					{
						cout << setw(2) << "*";
						check = 1;
					}
				}
			if(!check)
			{
				cout << setw(2) << board[i][j];
			}
			
		}
		cout << endl;
	}
	cout << endl;
}

