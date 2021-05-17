#pragma once
#include <conio.h>
#include <iostream>
#include <iomanip>
#include "board.h"
#define BOARDLEN 8
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class Player
{
public:
	Player();
	Player(int, Board&);
	bool OnMove(Board&, Position&, Position&);
	void OnPromote(Board& const board, Position& const pawnPos/*, PieceType& outType*/);
		// queen, rook, bishop or knight
	bool islegalPosition(Position);
	Position findKing(Board&);
	bool isThreatened(Board&, Position);
	void setAvailablePath(Board&);
	int camp;
};


Player::Player()
{
	camp = 0;
}
Player::Player(int c, Board& board)
{

	camp = c;
	setAvailablePath(board);
	
}
bool Player::OnMove(Board& board, Position& start, Position& end)
{
	if (!islegalPosition(start) || !islegalPosition(end))
		return 0;
	piece backup_chosen = board.board[start.x][start.y];
	piece& chosen = board.board[start.x][start.y];
	piece backup_destination = board.board[end.x][end.y];
	piece& destination = board.board[end.x][end.y];
	
	if (chosen.camp == destination.camp || chosen.camp != camp)//end cant be alley, start cant be enemy
		return 0;
	for (auto element : chosen.availablemove)
	{
		if (end.x == element.x && end.y == element.y)
		{
			destination = chosen;
			destination._position = end;
			destination.moved = true;
			chosen = piece();
			setAvailablePath(board);
			if (isThreatened(board, findKing(board)))
			{
				cout << "protect the king!\n";
				destination = backup_destination;
				chosen = backup_chosen;
				return 0;
			}
		}
	}
	for (auto element : chosen.attack)
	{
		if (end.x == element.x && end.y == element.y && destination.camp != NULL && destination.camp != camp)
		{
			destination = chosen;
			destination._position = end;
			destination.moved = true;
			chosen = piece();
			setAvailablePath(board);
			if (isThreatened(board, findKing(board)))
			{
				cout << "protect the king!\n";
				destination = backup_destination;
				chosen = backup_chosen;
				return 0;
			}
		}
	}
	board.print();
	return 1;
}

void Player::setAvailablePath(Board& board)
{
	//rook
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			if (board.board[i][j].camp == camp)
			{
				if (board.board[i][j].pieceId == ROOK)
				{
					//rook
					board.board[i][j].availablemove = vector<Position>();
					Position p = board.board[i][j]._position;
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
						if (islegalPosition(up) && board.board[up.x][up.y].camp != board.board[i][j].camp && !up_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(up);
							if (board.board[up.x][up.y].pieceId != null)
								up_crossing_piece = true;

						}
						else
						{
							up_crossing_piece = true;
						}
						if (islegalPosition(down) && board.board[down.x][down.y].camp != board.board[i][j].camp && !down_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(down);
							if (board.board[down.x][down.y].pieceId != null)
								down_crossing_piece = true;

						}
						else
						{
							down_crossing_piece = true;
						}

						if (islegalPosition(left) && board.board[left.x][left.y].camp != board.board[i][j].camp && !left_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(left);
							if (board.board[left.x][left.y].pieceId != null)
								left_crossing_piece = true;

						}
						else
						{
							left_crossing_piece = true;
						}

						if (islegalPosition(right) && board.board[right.x][right.y].camp != board.board[i][j].camp && !right_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(right);
							if (board.board[right.x][right.y].pieceId != null)
								right_crossing_piece = true;

						}
						else
						{
							right_crossing_piece = true;
						}
					}
				}
				else if (board.board[i][j].pieceId == PAWN)
				{
					board.board[i][j].availablemove = vector<Position>();
					Position forward_position = board.board[i][j]._position;
					forward_position.x = (camp == 0) ? forward_position.x - 1 : forward_position.x + 1;//determine where is front

					Position left = forward_position;
					Position right = forward_position;
					left.y -= 1;
					right.y += 1;

					if (islegalPosition(forward_position) && board.board[forward_position.x][forward_position.y].pieceId == null)
						board.board[i][j].availablemove.push_back(forward_position);
					if (islegalPosition(left) && board.board[left.x][left.y].camp != board.board[i][j].camp
						)//isEnemy
					{
						board.board[i][j].attack.push_back(left);
						if(board.board[left.x][left.y].pieceId != null)
							board.board[i][j].availablemove.push_back(left);
					}
					if (islegalPosition(right) && board.board[right.x][right.y].camp != board.board[i][j].camp
						)//isEnemy
					{
						board.board[i][j].attack.push_back(right);
						if (board.board[right.x][right.y].pieceId != null)
							board.board[i][j].availablemove.push_back(right);

					}


					//pawn has not moved
					Position two_step = forward_position;
					two_step.x = (camp == 0) ? forward_position.x - 1 : forward_position.x + 1;
					if (!board.board[i][j].moved)
					{
						if (islegalPosition(forward_position)
							&& board.board[two_step.x][two_step.y].pieceId == null
							&& board.board[forward_position.x][forward_position.y].pieceId == null)
							board.board[i][j].availablemove.push_back(two_step);
					}
				}
				else if (board.board[i][j].pieceId == BISHOP)
				{
					board.board[i][j].availablemove = vector<Position>();
					Position p = board.board[i][j]._position;
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
						if (islegalPosition(left_up) && board.board[left_up.x][left_up.y].camp != board.board[i][j].camp && !left_up_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(left_up);
							if (board.board[left_up.x][left_up.y].pieceId != null)
								left_up_crossing_piece = true;

						}
						else
						{
							left_up_crossing_piece = true;
						}
						if (islegalPosition(left_down) && board.board[left_down.x][left_down.y].camp != board.board[i][j].camp && !left_down_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(left_down);
							if (board.board[left_down.x][left_down.y].pieceId != null)
								left_down_crossing_piece = true;

						}
						else
						{
							left_down_crossing_piece = true;
						}

						if (islegalPosition(right_down) && board.board[right_down.x][right_down.y].camp != board.board[i][j].camp && !right_down_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(right_down);
							if (board.board[right_down.x][right_down.y].pieceId != null)
								right_down_crossing_piece = true;

						}
						else
						{
							right_down_crossing_piece = true;
						}

						if (islegalPosition(right_up) && board.board[right_up.x][right_up.y].camp != board.board[i][j].camp && !right_up_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(right_up);
							if (board.board[right_up.x][right_up.y].pieceId != null)
								right_up_crossing_piece = true;

						}
						else
						{
							right_up_crossing_piece = true;
						}

					}

				}
				else if (board.board[i][j].pieceId == KNIGHT)
				{
					board.board[i][j].availablemove = vector<Position>();
					Position p = board.board[i][j]._position;
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
						if (islegalPosition(check) && board.board[check.x][check.y].camp != board.board[i][j].camp)
						{
							board.board[i][j].availablemove.push_back(check);
						}

						//rotate
						tmp = p2.x;
						p2.x = p2.y;
						p2.y = -tmp;
						check.x = p.x + p2.x;
						check.y = p.y + p2.y;
						if (islegalPosition(check) && board.board[check.x][check.y].camp != board.board[i][j].camp)
						{
							board.board[i][j].availablemove.push_back(check);
						}
					}

				}
				else if (board.board[i][j].pieceId == KING)
				{
					board.board[i][j].availablemove = vector<Position>();
					Position p = board.board[i][j]._position;
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
					for (int K = 0; K < 4; K++)
					{
						int tmp = p1.x;
						p1.x = p1.y;
						p1.y = -tmp;
						check.x = p.x + p1.x;
						check.y = p.y + p1.y;
						if (islegalPosition(check) && board.board[check.x][check.y].camp != board.board[i][j].camp && !isThreatened(board, check))
						{
							board.board[i][j].availablemove.push_back(check);
						}

						tmp = p2.x;
						p2.x = p2.y;
						p2.y = -tmp;
						check.x = p.x + p2.x;
						check.y = p.y + p2.y;
						if (islegalPosition(check) && board.board[check.x][check.y].camp != board.board[i][j].camp && !isThreatened(board, check))
						{
							board.board[i][j].availablemove.push_back(check);
						}
					}
				}
				else if (board.board[i][j].pieceId == QUEEN)
				{
					board.board[i][j].availablemove = vector<Position>();
					Position p = board.board[i][j]._position;
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
						if (islegalPosition(left_up) && board.board[left_up.x][left_up.y].camp != board.board[i][j].camp && !left_up_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(left_up);
							if (board.board[left_up.x][left_up.y].pieceId != null)
								left_up_crossing_piece = true;

						}
						else
						{
							left_up_crossing_piece = true;
						}
						if (islegalPosition(left_down) && board.board[left_down.x][left_down.y].camp != board.board[i][j].camp && !left_down_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(left_down);
							if (board.board[left_down.x][left_down.y].pieceId != null)
								left_down_crossing_piece = true;

						}
						else
						{
							left_down_crossing_piece = true;
						}

						if (islegalPosition(right_down) && board.board[right_down.x][right_down.y].camp != board.board[i][j].camp && !right_down_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(right_down);
							if (board.board[right_down.x][right_down.y].pieceId != null)
								right_down_crossing_piece = true;

						}
						else
						{
							right_down_crossing_piece = true;
						}

						if (islegalPosition(right_up) && board.board[right_up.x][right_up.y].camp != board.board[i][j].camp && !right_up_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(right_up);
							if (board.board[right_up.x][right_up.y].pieceId != null)
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
						if (islegalPosition(up) && board.board[up.x][up.y].camp != board.board[i][j].camp && !up_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(up);
							if (board.board[up.x][up.y].pieceId != null)
								up_crossing_piece = true;

						}
						else
						{
							up_crossing_piece = true;
						}
						if (islegalPosition(down) && board.board[down.x][down.y].camp != board.board[i][j].camp && !down_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(down);
							if (board.board[down.x][down.y].pieceId != null)
								down_crossing_piece = true;

						}
						else
						{
							down_crossing_piece = true;
						}

						if (islegalPosition(left) && board.board[left.x][left.y].camp != board.board[i][j].camp && !left_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(left);
							if (board.board[left.x][left.y].pieceId != null)
								left_crossing_piece = true;

						}
						else
						{
							left_crossing_piece = true;
						}

						if (islegalPosition(right) && board.board[right.x][right.y].camp != board.board[i][j].camp && !right_crossing_piece)
						{
							board.board[i][j].availablemove.push_back(right);
							if (board.board[right.x][right.y].pieceId != null)
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
bool Player::islegalPosition(Position p)
{
	if (p.x >= 0 && p.x < BOARDLEN && p.y >= 0 && p.y < BOARDLEN)
	{
		return 1;
	}
	return 0;
}
bool Player::isThreatened(Board& board, Position king)
{
	for (int i = 0 ; i < BOARDLEN ; i++)
	{
		for (int j = 0 ; j < BOARDLEN ; j++)
		{
			if (board.board[i][j].camp != camp)
			{
				if (board.board[i][j].pieceId == PAWN)
				{
					for (auto element : board.board[i][j].attack)
					{
						if (element.x == king.x && element.y == king.y)
							return 1;
					}
				}
				else
				{
					for (auto element : board.board[i][j].availablemove)
					{
						if (element.x == king.x && element.y == king.y)
							return 1;
					}
				}
				
			}
		}
	}
	return 0;
}
Position Player::findKing(Board& board)
{
	Position king;
	for (int i = 0; i < BOARDLEN; i++)
	{
		for (int j = 0; j < BOARDLEN; j++)
		{
			if (board.board[i][j].pieceId == KING && board.board[i][j].camp == camp)
				king = board.board[i][j]._position;
		}
	}
	return king;
}
