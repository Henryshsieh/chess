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
	void OnMove(Board&); // 選擇要從 fromPos 走到 toPos
	void OnPromote(/*ex. Board& const board, Position& const
	pawnPos, PieceType& outType*/); // 選擇升階類型
	void chooseStart(Board&);
	void chooseEnd(Board&);
	void move(Board&, Position&, Position&);
	Position start;
	Position end;

private:
	int camp;
};

Player::Player()
{
	camp = 0;
}

void Player::OnMove(Board& board)
{
	chooseStart(board);
	chooseEnd(board);
	move(board, start, end);
}


void Player::chooseStart(Board& board)
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
					start.x += 1;

				break;
			case 80:
				start.x += 1;
				if (!(start.x < BOARDLEN && start.x >= 0 && start.y < BOARDLEN && start.y >= 0))
					start.x -= 1;
				break;
			case 75:
				start.y -= 1;
				if (!(start.x < BOARDLEN && start.x >= 0 && start.y < BOARDLEN && start.y >= 0))
					start.y += 1;
				break;
			case 77:
				start.y += 1;
				if (!(start.x < BOARDLEN && start.x >= 0 && start.y < BOARDLEN && start.y >= 0))
					start.y -= 1;
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

void Player::chooseEnd(Board& board)
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
					end.x += 1;

				break;
			case 80:
				end.x += 1;
				if (!(end.x < BOARDLEN && end.x >= 0 && end.y < BOARDLEN && end.y >= 0))
					end.x -= 1;
				break;
			case 75:
				end.y -= 1;
				if (!(end.x < BOARDLEN && end.x >= 0 && end.y < BOARDLEN && end.y >= 0))
					end.y += 1;
				break;
			case 77:
				end.y += 1;
				if (!(end.x < BOARDLEN && end.x >= 0 && end.y < BOARDLEN && end.y >= 0))
					end.y -= 1;
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


void Player::move(Board& board, Position& start, Position& end)
{
	switch (board.board[start.x][start.y].pieceId)
	{
	case null:
		cout << "null\n";
		break;
	case King:
		if (start.x != end.x || start.y != end.y && board.board[start.x][start.y].camp != board.board[end.x][end.y].camp) //不是同位置
		{
			if (abs(end.x - start.x) <= 1 && abs(end.y - start.y) <= 1)
			{
				board.board[end.x][end.y] = board.board[start.x][start.y];
				board.board[start.x][start.y] = piece();
			}
			else
			{
				cout << "cant move king\n";
			}

		}
		else
		{
			cout << "same position\n";
		}
		break;
	case Queen:
		if (start.x != end.x || start.y != end.y && board.board[start.x][start.y].camp != board.board[end.x][end.y].camp) //不是同位置
		{
			//同X horizontal
			if (start.x == end.x)
			{
				board.board[end.x][end.y] = board.board[start.x][start.y];
				board.board[start.x][start.y] = piece();
			}
			else if (start.y == end.y)
			{
				board.board[end.x][end.y] = board.board[start.x][start.y];
				board.board[start.x][start.y] = piece();
			}
			else if (abs(start.x - end.x) == abs(start.y - end.y)) //斜向
			{
				board.board[end.x][end.y] = board.board[start.x][start.y];
				board.board[start.x][start.y] = piece();
			}
			else
			{
				cout << "cant move queens \n";
			}
		}
		else
		{
			cout << "same position\n";
		}
		break;
	case Rook:

		if (start.x != end.x || start.y != end.y && board.board[start.x][start.y].camp != board.board[end.x][end.y].camp) //不是同位置
		{

			if (start.x == end.x) //同X
			{
				board.board[end.x][end.y] = board.board[start.x][start.y];
				board.board[start.x][start.y] = piece();
			}
			else if (start.y == end.y) //同Y
			{
				board.board[end.x][end.y] = board.board[start.x][start.y];
				board.board[start.x][start.y] = piece();
			}
			else {
				cout << "cant move rook\n";
			}
		}
		else
		{
			cout << "same position\n";
		}
		break;
	case Bishop:
		if (start.x != end.x || start.y != end.y && board.board[start.x][start.y].camp != board.board[end.x][end.y].camp) //不是同位置
		{
			if (abs(start.x - end.x) == abs(start.y - end.y)) //斜向
			{
				board.board[end.x][end.y] = board.board[start.x][start.y];
				board.board[start.x][start.y] = piece();
			}
			else
			{
				cout << "cant move bishop\n";
			}
		}
		else
		{
			cout << "same position\n";
		}
		break;
	case Knight:
		if ((abs(start.x - end.x) == 2 && abs(start.y - end.y) == 1) || (abs(start.x - end.x) == 1 && abs(start.y - end.y) == 2) && board.board[start.x][start.y].camp != board.board[end.x][end.y].camp) //日字
		{
			board.board[end.x][end.y] = board.board[start.x][start.y];
			board.board[start.x][start.y] = piece();
		}
		else
		{
			cout << "cant move knight\n";
		}
		break;
	case Pawn:
		if (board.board[end.x][end.y].camp != board.board[start.x][start.y].camp && start.x - end.x == 1 && abs(start.y - end.y) == 1)
		{
			board.board[end.x][end.y] = board.board[start.x][start.y];
			board.board[start.x][start.y] = piece();
		}
		else if (board.board[start.x][start.y].moved && start.x - end.x == 1 && board.board[end.x][end.y].pieceId == null && board.board[start.x][start.y].camp != board.board[end.x][end.y].camp)//moved
		{
			board.board[end.x][end.y] = board.board[start.x][start.y];
			board.board[start.x][start.y] = piece();
		}
		else if (!board.board[start.x][start.y].moved && start.x - end.x == 2 && board.board[end.x][end.y].pieceId == null && board.board[start.x][start.y].camp != board.board[end.x][end.y].camp)
		{
			board.board[start.x][start.y].moved = true;
			board.board[end.x][end.y] = board.board[start.x][start.y];
			board.board[start.x][start.y] = piece();

		}
		else
		{
			cout << "cant mobve\n";
		}
		break;
	default:
		break;
	}
}
