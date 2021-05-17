#pragma once
#include <conio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#define BOARDLEN 8
using namespace std;

struct Position { // the position of each piece
public:
	Position() :x(0), y(0) {}
	Position(int _x, int _y) :x(_x), y(_y) {}
	Position& operator =(Position rhs)
	{
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
	int x; // x, y coordinate
	int y;
};

enum mynum // types of chess pieces
{
	null = 0,
	KING = 1,
	QUEEN = 2,
	ROOK = 3,
	BISHOP = 4,
	KNIGHT = 5,
	PAWN = 6,
};

class piece // information regarding chess pieces
{
public:
	piece() :pieceId(null), camp(-999), pieceIndex(0), moved(0) {}
	piece(int id, int inx, int c, int x, int y) :pieceId(id), pieceIndex(inx), camp(c), moved(0), promotePiece(0)
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
	int promotePiece;
	int camp; // black side or white side; represented by 1 and 0 respectively
	bool moved = 0;
	piece& operator=(piece rhs)
	{
		pieceId = rhs.pieceId;
		pieceIndex = rhs.pieceIndex;
		promotePiece = rhs.promotePiece;
		camp = rhs.camp;
		moved = rhs.moved;
		_position = rhs._position;
		return *this;
	}
	Position _position;
	vector <Position> attack;
	vector <Position> availablemove;
};

class Board
{
public:
	piece board[BOARDLEN][BOARDLEN];
	void setAvailablePath();
	void print();
	bool isThreatened(Position king, int);
	bool islegalPosition(Position p);
	void print(Position);
	Board& operator = (Board rhs)
	{
		for (int i = 0; i < BOARDLEN; i++)
		{
			for (int j = 0; j < BOARDLEN; j++)
			{
				board[i][j] = rhs.board[i][j];
			}
		}
		return *this;
	}
	Board();
};

Board::Board() // constructor
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
	setAvailablePath();
}

bool Board::islegalPosition(Position p) // check if the chosen position is available
{
	if (p.x >= 0 && p.x < BOARDLEN && p.y >= 0 && p.y < BOARDLEN)
	{
		return 1;
	}
	return 0;
}

void Board::print() // print the board
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

void Board::print(Position p) // print the board
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
			else if (vec.size())
				for (auto element : vec)
				{
					if (i == element.x && j == element.y)
					{
						cout << setw(2) << "*";
						check = 1;
					}
				}
			if (!check)
			{
				cout << setw(2) << board[i][j];
			}

		}
		cout << endl;
	}
	cout << endl;
}

void Board::setAvailablePath() // set available paths
{
	//rook
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			board[i][j].availablemove = vector<Position>();
			board[i][j].attack = vector<Position>();

			if (1)
			{
				if (board[i][j].pieceId == ROOK)
				{
					//rook

					Position p = board[i][j]._position;
					Position up = p;
					Position down = p;
					Position left = p;
					Position right = p;
					bool up_crossing_piece = 0;
					bool down_crossing_piece = 0;
					bool left_crossing_piece = 0;
					bool right_crossing_piece = 0;

					for (int offset = 0; offset < BOARDLEN - 1; offset++)
					{
						up.x--;
						down.x++;
						left.y--;
						right.y++;
						if (islegalPosition(up) && board[up.x][up.y].camp != board[i][j].camp && !up_crossing_piece)
						{
							board[i][j].availablemove.push_back(up);
							if (board[up.x][up.y].pieceId != null)
								up_crossing_piece = true;

						}
						else
						{
							up_crossing_piece = true;
						}
						if (islegalPosition(down) && board[down.x][down.y].camp != board[i][j].camp && !down_crossing_piece)
						{
							board[i][j].availablemove.push_back(down);
							if (board[down.x][down.y].pieceId != null)
								down_crossing_piece = true;

						}
						else
						{
							down_crossing_piece = true;
						}

						if (islegalPosition(left) && board[left.x][left.y].camp != board[i][j].camp && !left_crossing_piece)
						{
							board[i][j].availablemove.push_back(left);
							if (board[left.x][left.y].pieceId != null)
								left_crossing_piece = true;

						}
						else
						{
							left_crossing_piece = true;
						}

						if (islegalPosition(right) && board[right.x][right.y].camp != board[i][j].camp && !right_crossing_piece)
						{
							board[i][j].availablemove.push_back(right);
							if (board[right.x][right.y].pieceId != null)
								right_crossing_piece = true;

						}
						else
						{
							right_crossing_piece = true;
						}
					}
				}
				else if (board[i][j].pieceId == PAWN)
				{

					Position forward_position = board[i][j]._position;
					forward_position.x = (board[i][j].camp == 0) ? forward_position.x - 1 : forward_position.x + 1;//determine where is front

					Position left = forward_position;
					Position right = forward_position;
					left.y -= 1;
					right.y += 1;

					if (islegalPosition(forward_position) && board[forward_position.x][forward_position.y].pieceId == null)
						board[i][j].availablemove.push_back(forward_position);
					if (islegalPosition(left) && board[left.x][left.y].camp != board[i][j].camp
						)//isEnemy
					{
						board[i][j].attack.push_back(left);
						if (board[left.x][left.y].pieceId != null)
							board[i][j].availablemove.push_back(left);
					}
					if (islegalPosition(right) && board[right.x][right.y].camp != board[i][j].camp
						)//isEnemy
					{
						board[i][j].attack.push_back(right);
						if (board[right.x][right.y].pieceId != null)
							board[i][j].availablemove.push_back(right);

					}


					//pawn has not moved
					Position two_step = forward_position;
					two_step.x = (board[i][j].camp == 0) ? forward_position.x - 1 : forward_position.x + 1;
					if (!board[i][j].moved)
					{
						if (islegalPosition(two_step)
							&& board[two_step.x][two_step.y].pieceId == null
							&& board[forward_position.x][forward_position.y].pieceId == null)
							board[i][j].availablemove.push_back(two_step);
					}
				}
				else if (board[i][j].pieceId == BISHOP)
				{

					Position p = board[i][j]._position;
					Position left_up = p;
					Position left_down = p;
					Position right_up = p;
					Position right_down = p;
					bool left_up_crossing_piece = 0;
					bool left_down_crossing_piece = 0;
					bool right_down_crossing_piece = 0;
					bool right_up_crossing_piece = 0;

					for (int offset = 0; offset < BOARDLEN - 1; offset++)
					{
						left_up.x--;
						left_up.y--;
						left_down.x++;
						left_down.y--;
						right_down.x++;
						right_down.y++;
						right_up.x--;
						right_up.y++;
						if (islegalPosition(left_up) && board[left_up.x][left_up.y].camp != board[i][j].camp && !left_up_crossing_piece)
						{
							board[i][j].availablemove.push_back(left_up);
							if (board[left_up.x][left_up.y].pieceId != null)
								left_up_crossing_piece = true;

						}
						else
						{
							left_up_crossing_piece = true;
						}
						if (islegalPosition(left_down) && board[left_down.x][left_down.y].camp != board[i][j].camp && !left_down_crossing_piece)
						{
							board[i][j].availablemove.push_back(left_down);
							if (board[left_down.x][left_down.y].pieceId != null)
								left_down_crossing_piece = true;

						}
						else
						{
							left_down_crossing_piece = true;
						}

						if (islegalPosition(right_down) && board[right_down.x][right_down.y].camp != board[i][j].camp && !right_down_crossing_piece)
						{
							board[i][j].availablemove.push_back(right_down);
							if (board[right_down.x][right_down.y].pieceId != null)
								right_down_crossing_piece = true;

						}
						else
						{
							right_down_crossing_piece = true;
						}

						if (islegalPosition(right_up) && board[right_up.x][right_up.y].camp != board[i][j].camp && !right_up_crossing_piece)
						{
							board[i][j].availablemove.push_back(right_up);
							if (board[right_up.x][right_up.y].pieceId != null)
								right_up_crossing_piece = true;

						}
						else
						{
							right_up_crossing_piece = true;
						}

					}

				}
				else if (board[i][j].pieceId == KNIGHT)
				{

					Position p = board[i][j]._position;
					Position p1;
					Position p2;
					Position check;
					p1.x = 2;
					p1.y = 1;
					p2.x = 1;
					p2.y = 2;
					for (int offset = 0; offset < 4; offset++)
					{
						//rotate
						int tmp = p1.x;
						p1.x = p1.y;
						p1.y = -tmp;
						check.x = p.x + p1.x;
						check.y = p.y + p1.y;
						if (islegalPosition(check) && board[check.x][check.y].camp != board[i][j].camp)
						{
							board[i][j].availablemove.push_back(check);
						}

						//rotate
						tmp = p2.x;
						p2.x = p2.y;
						p2.y = -tmp;
						check.x = p.x + p2.x;
						check.y = p.y + p2.y;
						if (islegalPosition(check) && board[check.x][check.y].camp != board[i][j].camp)
						{
							board[i][j].availablemove.push_back(check);
						}
					}

				}
				else if (board[i][j].pieceId == KING)
				{

					Position p = board[i][j]._position;
					Position p1;
					Position p2;
					Position check;
					p1.x = 1;
					p1.y = 1;
					p2.x = 1;
					p2.y = 0;
					//xxo
					//xxo <-rotate
					//xxx
					for (int qq = 0; qq < BOARDLEN; qq++)
					{
						for (int pp = 0; pp < BOARDLEN; pp++)
						{
							if (board[qq][pp].camp == board[i][j].camp && board[qq][pp].pieceId == ROOK)
							{
								Position rook = board[qq][pp]._position;
								bool moveHorizontal = 0;
								bool moveVertical = 0;
								if (board[rook.x][rook.y].availablemove.empty() || board[p.x][p.y].moved || board[qq][pp].moved)
								{
									moveHorizontal = 1;
									moveVertical = 1;
								}
								for (auto element : board[rook.x][rook.y].availablemove)
								{
									if (element.x - p.x == 0 && !moveHorizontal)
									{
										if (isThreatened(element, board[p.x][p.y].camp))
											moveHorizontal = 1;
									}
									else if (element.y == p.y && !moveVertical)
									{
										if (isThreatened(element, board[p.x][p.y].camp))
											moveHorizontal = 1;
									}
								}
								if (!moveHorizontal || !moveVertical)
									board[p.x][p.y].availablemove.push_back(rook);

							}
						}
					}


					for (int K = 0; K < 4; K++)
					{
						int tmp = p1.x;
						p1.x = p1.y;
						p1.y = -tmp;
						check.x = p.x + p1.x;
						check.y = p.y + p1.y;
						if (islegalPosition(check) && board[check.x][check.y].camp != board[i][j].camp && !isThreatened(check, board[p.x][p.y].camp))
						{
							board[i][j].availablemove.push_back(check);
						}

						tmp = p2.x;
						p2.x = p2.y;
						p2.y = -tmp;
						check.x = p.x + p2.x;
						check.y = p.y + p2.y;
						if (islegalPosition(check) && board[check.x][check.y].camp != board[i][j].camp && !isThreatened(check, board[p.x][p.y].camp))
						{
							board[i][j].availablemove.push_back(check);
						}
					}
				}
				else if (board[i][j].pieceId == QUEEN)
				{

					Position p = board[i][j]._position;
					Position up = p;
					Position down = p;
					Position left = p;
					Position right = p;
					Position left_up = p;
					Position left_down = p;
					Position right_up = p;
					Position right_down = p;

					bool up_crossing_piece = 0;
					bool down_crossing_piece = 0;
					bool left_crossing_piece = 0;
					bool right_crossing_piece = 0;

					bool left_up_crossing_piece = 0;
					bool left_down_crossing_piece = 0;
					bool right_down_crossing_piece = 0;
					bool right_up_crossing_piece = 0;

					for (int offset = 0; offset < BOARDLEN - 1; offset++)
					{
						left_up.x--;
						left_up.y--;
						left_down.x++;
						left_down.y--;
						right_down.x++;
						right_down.y++;
						right_up.x--;
						right_up.y++;
						if (islegalPosition(left_up) && board[left_up.x][left_up.y].camp != board[i][j].camp && !left_up_crossing_piece)
						{
							board[i][j].availablemove.push_back(left_up);
							if (board[left_up.x][left_up.y].pieceId != null)
								left_up_crossing_piece = true;

						}
						else
						{
							left_up_crossing_piece = true;
						}
						if (islegalPosition(left_down) && board[left_down.x][left_down.y].camp != board[i][j].camp && !left_down_crossing_piece)
						{
							board[i][j].availablemove.push_back(left_down);
							if (board[left_down.x][left_down.y].pieceId != null)
								left_down_crossing_piece = true;

						}
						else
						{
							left_down_crossing_piece = true;
						}

						if (islegalPosition(right_down) && board[right_down.x][right_down.y].camp != board[i][j].camp && !right_down_crossing_piece)
						{
							board[i][j].availablemove.push_back(right_down);
							if (board[right_down.x][right_down.y].pieceId != null)
								right_down_crossing_piece = true;

						}
						else
						{
							right_down_crossing_piece = true;
						}

						if (islegalPosition(right_up) && board[right_up.x][right_up.y].camp != board[i][j].camp && !right_up_crossing_piece)
						{
							board[i][j].availablemove.push_back(right_up);
							if (board[right_up.x][right_up.y].pieceId != null)
								right_up_crossing_piece = true;

						}
						else
						{
							right_up_crossing_piece = true;
						}
					}
					for (int offset = 0; offset < BOARDLEN - 1; offset++)
					{
						up.x--;
						down.x++;
						left.y--;
						right.y++;
						if (islegalPosition(up) && board[up.x][up.y].camp != board[i][j].camp && !up_crossing_piece)
						{
							board[i][j].availablemove.push_back(up);
							if (board[up.x][up.y].pieceId != null)
								up_crossing_piece = true;

						}
						else
						{
							up_crossing_piece = true;
						}
						if (islegalPosition(down) && board[down.x][down.y].camp != board[i][j].camp && !down_crossing_piece)
						{
							board[i][j].availablemove.push_back(down);
							if (board[down.x][down.y].pieceId != null)
								down_crossing_piece = true;

						}
						else
						{
							down_crossing_piece = true;
						}

						if (islegalPosition(left) && board[left.x][left.y].camp != board[i][j].camp && !left_crossing_piece)
						{
							board[i][j].availablemove.push_back(left);
							if (board[left.x][left.y].pieceId != null)
								left_crossing_piece = true;

						}
						else
						{
							left_crossing_piece = true;
						}

						if (islegalPosition(right) && board[right.x][right.y].camp != board[i][j].camp && !right_crossing_piece)
						{
							board[i][j].availablemove.push_back(right);
							if (board[right.x][right.y].pieceId != null)
								right_crossing_piece = true;

						}
						else
						{
							right_crossing_piece = true;
						}

					}
				}
			}

		}
	}
	//knight
	//cos sin 
	//-sin cos
	//0 1
	//-1 0
	//y , -x
}

bool Board::isThreatened(Position king, int camp) // see if "check" occurs, that is, if the king is threatened
{
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			if (board[i][j].camp != camp)
			{
				if (board[i][j].pieceId == PAWN)
				{
					for (auto element : board[i][j].attack)
					{
						if (element.x == king.x && element.y == king.y)
						{
							cout << board[king.x][king.y].camp << " king threatened from" << board[i][j] << "      " << i << " " << j << endl;
							print(element);
							return 1;

						}
					}
				}
				else
				{
					for (auto element : board[i][j].availablemove)
					{
						if (element.x == king.x && element.y == king.y)
						{
							cout << board[king.x][king.y].camp << " king threatened from" << board[i][j] << "      " << i << " " << j << endl;
							print(element);
							return 1;

						}
					}
				}

			}
		}
	}
	return 0;
}