#pragma once
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
	void refresh();
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
}
Player::Player(int c, Board& board)
{

	piece* ptr = (piece*)(board.board);
	if (c == 0)
	{
		rook[0] = (ptr + 7 * BOARDLEN + 0);
		knight[0] = (ptr + 7 * BOARDLEN + 1);
		bishop[0] = (ptr + 7 * BOARDLEN + 2);
		queen = (ptr + 7 * BOARDLEN + 3);
		king = (ptr + 7 * BOARDLEN + 4);

		bishop[1] = (ptr + 7 * BOARDLEN + 56);
		knight[1] = (ptr + 7 * BOARDLEN + 6);
		rook[1] = (ptr + 7 * BOARDLEN + 7);
		for (int i = 0; i < BOARDLEN; i++)
		{
			pawn[i] = (ptr + 6 * BOARDLEN + i);
		}
	}
	else
	{
		rook[0] = (ptr + 0 * BOARDLEN + 0);
		knight[0] = (ptr + 0 * BOARDLEN + 1);
		bishop[0] = (ptr + 0 * BOARDLEN + 2);
		queen = (ptr + 0 * BOARDLEN + 3);
		king = (ptr + 0 * BOARDLEN + 4);
		bishop[1] = (ptr + 0 * BOARDLEN + 5);
		knight[1] = (ptr + 0 * BOARDLEN + 6);
		rook[1] = (ptr + 0 * BOARDLEN + 7);
		for (int i = 0; i < BOARDLEN; i++)
		{
			pawn[i] = (ptr + 1 * BOARDLEN + i);
		}
	}
	//set available path
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
				if (!(start.x < BOARDLEN && start.x >= 0 && start.y < BOARDLEN && start.y >= 0))
				{
					cout << "choose again\n";
					start.x += 1;
				}

				break;
			case 80:
				start.x += 1;
				if (!(start.x < BOARDLEN && start.x >= 0 && start.y < BOARDLEN && start.y >= 0))
				{
					cout << "choose again\n";
					start.x -= 1;
				}
				break;
			case 75:
				start.y -= 1;
				if (!(start.x < BOARDLEN && start.x >= 0 && start.y < BOARDLEN && start.y >= 0))
				{
					cout << "choose again\n";
					start.y += 1;
				}
				break;
			case 77:
				start.y += 1;
				if (!(start.x < BOARDLEN && start.x >= 0 && start.y < BOARDLEN && start.y >= 0))
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
				if (!(end.x < BOARDLEN && end.x >= 0 && end.y < BOARDLEN && end.y >= 0))
				{
					cout << "choose again\n";
					end.x += 1;
				}
				break;
			case 80:
				end.x += 1;
				if (!(end.x < BOARDLEN && end.x >= 0 && end.y < BOARDLEN && end.y >= 0))
				{
					cout << "choose again\n";
					end.x += 1;
				}
				break;
			case 75:
				end.y -= 1;
				if (!(end.x < BOARDLEN && end.x >= 0 && end.y < BOARDLEN && end.y >= 0))
				{
					cout << "choose again\n";
					end.x += 1;
				}
				break;
			case 77:
				end.y += 1;
				if (!(end.x < BOARDLEN && end.x >= 0 && end.y < BOARDLEN && end.y >= 0))
				{
					cout << "choose again\n";
					end.x += 1;
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

void Player::refresh()
{
	if (king->camp != camp)
		king = NULL;
	if (queen->camp != camp)
		queen = NULL;
	for (int i = 0; i < 2; i++)
	{
		if (bishop[i]->camp != camp)
			bishop[i] = NULL;
		if (knight[i]->camp != camp)
			knight[i] = NULL;
		if (rook[i]->camp != camp)
			rook[i] = NULL;
	}
	for (int i = 0 ; i <  8 ; i ++)
	{
		if (pawn[i]->camp != camp)
			pawn[i] = NULL;
	}

}

void Player::setAvailablePath(Board& board)
{
	for (int i = 0; i < 2; i++)
	{
		Position p = rook[i]->_position;
		for (int offset = p.x; offset < BOARDLEN - 1;)
		{
			offset++;
			if (p.x + offset >= 0 && p.x + offset < BOARDLEN)
			{
				if (board.board[p.x + offset][p.y].camp != rook[i]->camp)
					rook[i]->availbe.push_back(Position(p.x + offset, p.y));
				else
					break;
			}
			if (p.x - offset >= 0 && p.x - offset < BOARDLEN)
			{
				if (board.board[p.x - offset][p.y].camp != rook[i]->camp)
					rook[i]->availbe.push_back(Position(p.x - offset, p.y));
				else
					break;
			}
		}
		for (int offset = p.y; offset < BOARDLEN - 1;)
		{
			offset++;
			if (p.y + offset >= 0 && p.y + offset < BOARDLEN)
			{
				if (board.board[p.x][p.y + offset].camp != rook[i]->camp)
					rook[i]->availbe.push_back(Position(p.x, p.y + offset));
				else
					break;
			}
			if (p.y - offset >= 0 && p.y - offset < BOARDLEN)
			{
				if (board.board[p.x][p.y - offset].camp != rook[i]->camp)
					rook[i]->availbe.push_back(Position(p.x, p.y - offset));
				else
					break;
			}
		}

	}

}
