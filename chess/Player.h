﻿#pragma once
#include <conio.h>
#include <iostream>
#include <iomanip>
#include "board.h"
#define BOARDLEN 8
using namespace std;

class Player
{
public:
	Player();
	Player(int, Board&);
	void OnMove(Board&, Position&, Position&);
	void OnPromote(Board& const board, Position& const pawnPos/*, PieceType& outType*/);
		// queen, rook, bishop or knight
	void chooseStart(Board&, Position&, Position&);
	void chooseEnd(Board&, Position&, Position&);
	bool islegalPosition(Position);
	void refresh(Board&);
	bool isThreatened(Board&, Position);
	void setAvailablePath(Board&);
	int camp;
	piece* king;
	piece* queen;
	piece* bishop[2];
	piece* knight[2];
	piece* rook[2];
	piece* pawn[8];
};


Player::Player()
{
	camp = 0;
	rook[0] = NULL;
	knight[0] = NULL;
	bishop[0] = NULL;
	queen = NULL;
	king = NULL;
	bishop[1] = NULL;
	knight[1] = NULL;
	rook[1] = NULL;

	for (int i = 0; i < BOARDLEN; i++)
	{
		pawn[i] = NULL;
	}
}
Player::Player(int c, Board& board)
{

	piece* ptr = (piece*)(board.board);
	if (c == 0)
	{
		rook[0] = &board.board[7][0];
		knight[0] = &board.board[7][1];
		bishop[0] = &board.board[7][2];
		queen = &board.board[7][3];
		king = &board.board[7][4];
		bishop[1] = &board.board[7][5];
		knight[1] = &board.board[7][6];
		rook[1] = &board.board[7][7];

		for (int i = 0; i < BOARDLEN; i++)
		{
			pawn[i] = &board.board[6][i];
		}
	}
	else
	{
		rook[0] = &board.board[0][0];
		knight[0] = &board.board[0][1];
		bishop[0] = &board.board[0][2];
		queen = &board.board[0][3];
		king = &board.board[0][4];
		bishop[1] = &board.board[0][5];
		knight[1] = &board.board[0][6];
		rook[1] = &board.board[0][7];

		for (int i = 0; i < BOARDLEN; i++)
		{
			pawn[i] = &board.board[1][i];
		}
	}
	camp = c;
	setAvailablePath(board);
	
}
void Player::OnMove(Board& board, Position& start, Position& end)
{
	chooseStart(board, start, end);
	chooseEnd(board, start, end);
}

void Player::chooseStart(Board& board, Position& start, Position& end)
{
	char key1 = '0', key2;
	start.x = BOARDLEN / 2;
	start.y = BOARDLEN / 2;
	while (key1 != 'q')
	{
		board.print(start);
		key1 = _getch();
		switch (key1)
		{
		case -32:
			key2 = _getch();
			switch (key2)
			{
			case 72:
				start.x -= 1;
				if (!islegalPosition(start))
				{
					cout << "choose again\n";
					start.x += 1;
				}

				break;
			case 80:
				start.x += 1;
				if (!islegalPosition(start))
				{
					cout << "choose again\n";
					start.x -= 1;
				}
				break;
			case 75:
				start.y -= 1;
				if (!islegalPosition(start))
				{
					cout << "choose again\n";
					start.y += 1;
				}
				break;
			case 77:
				start.y += 1;
				if (!islegalPosition(start))
				{
					cout << "choose again\n";
					start.y -= 1;
				}
				break;
			default:
				break;
			}
			break;
		default:
			if (int(key1) == 13)
				key1 = 'q';
		}
	}
	end = start;
}

void Player::chooseEnd(Board& board, Position& start, Position& end)
{
	char key1 = '0', key2;
	while (key1 != 'q')
	{
		board.print(end);
		key1 = _getch();
		switch (key1)
		{
		case -32:
			key2 = _getch();
			switch (key2)
			{
			case 72:
				end.x -= 1;
				if (!islegalPosition(end))
				{
					cout << "choose again\n";
					end.x += 1;
				}
				break;
			case 80:
				end.x += 1;
				if (!islegalPosition(end))
				{
					cout << "choose again\n";
					end.x -= 1;
				}
				break;
			case 75:
				end.y -= 1;
				if (!islegalPosition(end))
				{
					cout << "choose again\n";
					end.y += 1;
				}
				break;
			case 77:
				end.y += 1;
				if (!islegalPosition(end))
				{
					cout << "choose again\n";
					end.y -= 1;
				}

				break;
			default:
				break;
			}
			break;
		default:
			if (int(key1) == 13)
				key1 = 'q';
		}
	}
}


void Player::setAvailablePath(Board& board)
{
	//rook
	for (int i = 0; i < 2; i++)
	{
		if (rook[i] == NULL)
			continue;
		rook[i]->availbe = vector<Position>();
		Position p = rook[i]->_position;
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
			if (islegalPosition(up) && board.board[up.x][up.y].camp != rook[i]->camp && !up_crossing_piece)
			{
				rook[i]->availbe.push_back(up);
				if(board.board[up.x][up.y].pieceId != null)
					up_crossing_piece = true;

			}
			else
			{
				up_crossing_piece = true;
			}
			if (islegalPosition(down) && board.board[down.x][down.y].camp != rook[i]->camp && !down_crossing_piece)
			{
				rook[i]->availbe.push_back(down);
				if (board.board[down.x][down.y].pieceId != null)
					down_crossing_piece = true;

			}
			else
			{
				down_crossing_piece = true;
			}

			if (islegalPosition(left) && board.board[left.x][left.y].camp != rook[i]->camp && !left_crossing_piece)
			{
				rook[i]->availbe.push_back(left);
				if (board.board[left.x][left.y].pieceId != null)
					left_crossing_piece = true;

			}
			else
			{
				left_crossing_piece = true;
			}

			if (islegalPosition(right) && board.board[right.x][right.y].camp != rook[i]->camp && !right_crossing_piece)
			{
				rook[i]->availbe.push_back(right);
				if (board.board[right.x][right.y].pieceId != null)
					right_crossing_piece = true;

			}
			else
			{
				right_crossing_piece = true;
			}

		}
	}

	//pawn
	for (int i = 0 ; i < BOARDLEN ; i ++)
	{
		if(pawn[i] == NULL)
			continue;
		pawn[i]->availbe = vector<Position>();
		Position forward_position = pawn[i]->_position;
		forward_position.x = (camp == 0) ? forward_position.x - 1 : forward_position.x + 1;//determine where is front
		
		Position left = forward_position;
		Position right = forward_position;
		left.y -= 1;
		right.y += 1;

		if(islegalPosition(forward_position) && board.board[forward_position.x][forward_position.y].pieceId == null)
			pawn[i]->availbe.push_back(forward_position);
		if (islegalPosition(left) && board.board[left.x][left.y].camp != pawn[i]->camp
			&& board.board[left.x][left.y].pieceId != null)//isEnemy
		{
			pawn[i]->availbe.push_back(left);
		}
		if (islegalPosition(right) && board.board[right.x][right.y].camp != pawn[i]->camp
			&& board.board[right.x][right.y].pieceId != null)//isEnemy
		{
			pawn[i]->availbe.push_back(right);
		}


		//pawn has not moved
		Position two_step = forward_position;
		two_step.x = (camp == 0) ? forward_position.x - 1 : forward_position.x + 1;
		if (!pawn[i]->moved)
		{
			if (islegalPosition(forward_position) 
				&& board.board[two_step.x][two_step.y].pieceId == null
				&& board.board[forward_position.x][forward_position.y].pieceId == null)
				pawn[i]->availbe.push_back(two_step);
		}
	}

	//bishop
	for (int i = 0; i < 2; i++)
	{
		if (bishop[i] == NULL)
			continue;
		bishop[i]->availbe = vector<Position>();
		Position p = bishop[i]->_position;
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
			if (islegalPosition(left_up) && board.board[left_up.x][left_up.y].camp != bishop[i]->camp && !left_up_crossing_piece)
			{
				bishop[i]->availbe.push_back(left_up);
				if (board.board[left_up.x][left_up.y].pieceId != null)
					left_up_crossing_piece = true;

			}
			else
			{
				left_up_crossing_piece = true;
			}
			if (islegalPosition(left_down) && board.board[left_down.x][left_down.y].camp != bishop[i]->camp && !left_down_crossing_piece)
			{
				bishop[i]->availbe.push_back(left_down);
				if (board.board[left_down.x][left_down.y].pieceId != null)
					left_down_crossing_piece = true;
				
			}
			else
			{
				left_down_crossing_piece = true;
			}

			if (islegalPosition(right_down) && board.board[right_down.x][right_down.y].camp != bishop[i]->camp && !right_down_crossing_piece)
			{
				bishop[i]->availbe.push_back(right_down);
				if (board.board[right_down.x][right_down.y].pieceId != null)
					right_down_crossing_piece = true;

			}
			else
			{
				right_down_crossing_piece = true;
			}

			if (islegalPosition(right_up) && board.board[right_up.x][right_up.y].camp != bishop[i]->camp && !right_up_crossing_piece)
			{
				bishop[i]->availbe.push_back(right_up);
				if (board.board[right_up.x][right_up.y].pieceId != null)
					right_up_crossing_piece = true;

			}
			else
			{
				right_up_crossing_piece = true;
			}

		}
	}

	//knight
	//cos sin 
	//-sin cos
	//0 1
	//-1 0
	//y , -x
	for (int i = 0; i < 2; i++)
	{
		if(knight[i] == NULL)
			continue;
		knight[i]->availbe = vector<Position>();
		Position p = knight[i]->_position;
		Position p1;
		Position p2;
		Position check;
		p1.x = 2;
		p1.y = 1;
		p2.x = 1;
		p2.y = 2;
		for (int j = 0 ; j < 4 ; j ++)
		{
			//rotate
			int tmp = p1.x;
			p1.x = p1.y;
			p1.y = -tmp;
			check.x = p.x + p1.x;
			check.y = p.y + p1.y;
			if (islegalPosition(check) && board.board[check.x][check.y].camp != knight[i]->camp)
			{
				knight[i]->availbe.push_back(check);
			}

			//rotate
			tmp = p2.x;
			p2.x = p2.y;
			p2.y = -tmp;
			check.x = p.x + p2.x;
			check.y = p.y + p2.y;
			if (islegalPosition(check) && board.board[check.x][check.y].camp != knight[i]->camp)
			{
				knight[i]->availbe.push_back(check);
			}
		}
	}

	//king
	if (king != NULL)
	{
		king->availbe = vector<Position>();
		Position p = king->_position;
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
		for (int j = 0; j < 4; j++)
		{
			int tmp = p1.x;
			p1.x = p1.y;
			p1.y = -tmp;
			check.x = p.x + p1.x;
			check.y = p.y + p1.y;
			if (islegalPosition(check) && board.board[check.x][check.y].camp != king->camp && !isThreatened(board, check))
			{
				king->availbe.push_back(check);
			}

			tmp = p2.x;
			p2.x = p2.y;
			p2.y = -tmp;
			check.x = p.x + p2.x;
			check.y = p.y + p2.y;
			if (islegalPosition(check) && board.board[check.x][check.y].camp != king->camp && !isThreatened(board, check))
			{
				king->availbe.push_back(check);
			}
		}
	}
	//queen

	if (queen != NULL)
	{
		queen->availbe = vector<Position>();
		Position p = queen->_position;
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
			if (islegalPosition(left_up) && board.board[left_up.x][left_up.y].camp != queen->camp && !left_up_crossing_piece)
			{
				queen->availbe.push_back(left_up);
				if (board.board[left_up.x][left_up.y].pieceId != null)
					left_up_crossing_piece = true;

			}
			else
			{
				left_up_crossing_piece = true;
			}
			if (islegalPosition(left_down) && board.board[left_down.x][left_down.y].camp != queen->camp && !left_down_crossing_piece)
			{
				queen->availbe.push_back(left_down);
				if (board.board[left_down.x][left_down.y].pieceId != null)
					left_down_crossing_piece = true;

			}
			else
			{
				left_down_crossing_piece = true;
			}

			if (islegalPosition(right_down) && board.board[right_down.x][right_down.y].camp != queen->camp && !right_down_crossing_piece)
			{
				queen->availbe.push_back(right_down);
				if (board.board[right_down.x][right_down.y].pieceId != null)
					right_down_crossing_piece = true;

			}
			else
			{
				right_down_crossing_piece = true;
			}

			if (islegalPosition(right_up) && board.board[right_up.x][right_up.y].camp != queen->camp && !right_up_crossing_piece)
			{
				queen->availbe.push_back(right_up);
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
			if (islegalPosition(up) && board.board[up.x][up.y].camp != queen->camp && !up_crossing_piece)
			{
				queen->availbe.push_back(up);
				if (board.board[up.x][up.y].pieceId != null)
					up_crossing_piece = true;

			}
			else
			{
				up_crossing_piece = true;
			}
			if (islegalPosition(down) && board.board[down.x][down.y].camp != queen->camp && !down_crossing_piece)
			{
				queen->availbe.push_back(down);
				if (board.board[down.x][down.y].pieceId != null)
					down_crossing_piece = true;

			}
			else
			{
				down_crossing_piece = true;
			}

			if (islegalPosition(left) && board.board[left.x][left.y].camp != queen->camp && !left_crossing_piece)
			{
				queen->availbe.push_back(left);
				if (board.board[left.x][left.y].pieceId != null)
					left_crossing_piece = true;

			}
			else
			{
				left_crossing_piece = true;
			}

			if (islegalPosition(right) && board.board[right.x][right.y].camp != queen->camp && !right_crossing_piece)
			{
				queen->availbe.push_back(right);
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

bool Player::islegalPosition(Position p)
{
	if (p.x >= 0 && p.x < BOARDLEN && p.y >= 0 && p.y < BOARDLEN)
	{
		return 1;
	}
	return 0;
}

bool Player::isThreatened(Board& board, Position p)
{

	for (int i = 0 ; i < BOARDLEN ; i++)
	{
		for (int j = 0 ; j < BOARDLEN ; j++)
		{
			if (board.board[i][j].camp != board.board[p.x][p.y].camp)
			{
				for (auto element : board.board[i][j].availbe)
				{
					if (element.x == p.x && element.y == p.y)
						return 1;
				}
			}
		}
	}
	return 0;
}

void Player::OnPromote(Board& const board, Position& const pawnPos/*, PieceType& outType*/)
{
	for (int i = 0 ; i < BOARDLEN ; i++)
	{
		int n = -1;
		int check = 0;
		if (camp == 0)
			check = 0;
		else
			check = 7;
		while (pawn[i]->_position.x == check && !(n <= 4 && n >= 1))
		{
			cout << "promote pawn:\n";
			cout << "1.queen\n";
			cout << "2.rook\n";
			cout << "3.bishop\n";
			cout << "4.knight\n";
			cin >> n;
			switch (n)
			{
			case 1:
				pawn[i]->pieceId = QUEEN;
				break;
			case 2:
				pawn[i]->pieceId = ROOK;
				break;
			case 3:
				pawn[i]->pieceId = BISHOP;
				break;
			case 4:
				pawn[i]->pieceId = KNIGHT;
				break;
			default:
				break;
			}
		}
	}
	
}



void Player::refresh(Board& board)
{
	for (int index = 0; index < 2; index++)
	{
		setAvailablePath(board);
		if (king != NULL && king->camp != camp)
			king = NULL;
		if (queen != NULL && queen->camp != camp)
			queen = NULL;
		for (int i = 0; i < 2; i++)
		{
			if (bishop != NULL && bishop[i]->camp != camp)
				bishop[i] = NULL;
			if (knight[i] != NULL && knight[i]->camp != camp)
				knight[i] = NULL;
			if (rook[i]->camp != camp)
				rook[i] = NULL;
		}
		for (int i = 0; i < 8; i++)
		{
			if (pawn[i] != NULL && pawn[i]->camp != camp)
				pawn[i] = NULL;
		}

	}

}
