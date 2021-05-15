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
	Player(int);
	void OnMove(Board&, Position&, Position&); // 選擇要從 fromPos 走到 toPos
	void OnPromote(/*ex. Board& const board, Position& const
	pawnPos, PieceType& outType*/); // 選擇升階類型
	void chooseStart(Board&, Position&, Position&);
	void chooseEnd(Board&, Position&, Position&);
	
private:
	int camp;
};

Player::Player()
{
	camp = 0;
}
Player::Player(int c)
{
	camp = c;
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
