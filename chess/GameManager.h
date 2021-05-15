#pragma once
#include "Player.h"
#include "Viewer.h"
class GameManger
{
public:
	GameManger();
	~GameManger();
	void run();
	bool move(Board&, Position&, Position&);
	Position start;
	Position end;

private:
	Player players[2];
	int current_player;
	Viewer viewer;
	Board board;
};
void GameManger::run()
{
	while (true)
	{
		if (current_player == 0)
		{
			cout << "player0\n";
			players[0].OnMove(board, start, end);
			if(move(board, start, end))
				current_player = 1;

		}
		else
		{
			cout << "player1\n";
			players[1].OnMove(board, start, end);
			if (move(board, start, end))
				current_player = 0;
		}
	}
}

GameManger::GameManger()
{
	board = Board();
	viewer = Viewer();
	players[0] = Player(0);
	players[1] = Player(1);
	current_player = 0;
	start.x = 0;
	start.y = 0;
	end.x = 0;
	end.y = 0;
}

GameManger::~GameManger()
{
}





bool GameManger::move(Board& board, Position& start, Position& end)
{
	piece& chosen = board.board[start.x][start.y];
	piece& destination = board.board[end.x][end.y];
	switch (chosen.pieceId)
	{
	case null:
		cout << "null\n";
		return 0;
	case King:
		if (start.x != end.x || start.y != end.y && chosen.camp != destination.camp) //不是同位置
		{
			if (abs(end.x - start.x) <= 1 && abs(end.y - start.y) <= 1)
			{
				destination = chosen;
				chosen = piece();
			}
			else
			{
				cout << "cant move king\n";
				return 0;
			}

		}
		else
		{
			cout << "same position\n";
			return 0;
		}
		return 1;
	case Queen:
		if (start.x != end.x || start.y != end.y && chosen.camp != destination.camp) //不是同位置
		{
			//同X horizontal
			if (start.x == end.x)
			{
				destination = chosen;
				chosen = piece();
			}
			else if (start.y == end.y)
			{
				destination = chosen;
				chosen = piece();
			}
			else if (abs(start.x - end.x) == abs(start.y - end.y)) //斜向
			{
				destination = chosen;
				chosen = piece();
			}
			else
			{
				cout << "cant move queens \n";
				return 0;
			}
		}
		else
		{
			cout << "same position\n";
			return 0;
		}
		return 1;
	case Rook:

		if (start.x != end.x || start.y != end.y && chosen.camp != destination.camp) //不是同位置
		{

			if (start.x == end.x) //同X
			{
				destination = chosen;
				chosen = piece();
			}
			else if (start.y == end.y) //同Y
			{
				destination = chosen;
				chosen = piece();
			}
			else {
				cout << "cant move rook\n";
				return 0;
			}
		}
		else
		{
			cout << "same position\n";
			return 0;
		}
		return 1;
	case Bishop:
		if (start.x != end.x || start.y != end.y && chosen.camp != destination.camp) //不是同位置
		{
			if (abs(start.x - end.x) == abs(start.y - end.y)) //斜向
			{
				destination = chosen;
				chosen = piece();
			}
			else
			{
				cout << "cant move bishop\n";
				return 0;
			}
		}
		else
		{
			cout << "same position\n";
			return 0;
		}
		return 1;
	case Knight:
		if ((abs(start.x - end.x) == 2 && abs(start.y - end.y) == 1) || (abs(start.x - end.x) == 1 && abs(start.y - end.y) == 2) && chosen.camp != destination.camp) //日字
		{
			destination = chosen;
			chosen = piece();
		}
		else
		{
			cout << "cant move knight\n";
			return 0;
		}
		return 1;
	case Pawn:
		if (current_player == 0)
		{
			if (destination.camp != chosen.camp && start.x - end.x == 1 && abs(start.y - end.y) == 1)
			{
				destination = chosen;
				chosen = piece();
			}
			else if (chosen.moved && start.x - end.x == 1 && destination.pieceId == null && chosen.camp != destination.camp)//moved
			{
				destination = chosen;
				chosen = piece();
			}
			else if (!chosen.moved && start.x - end.x == 2 && destination.pieceId == null && chosen.camp != destination.camp)
			{
				chosen.moved = true;
				destination = chosen;
				chosen = piece();

			}
			else
			{
				cout << "cant mobve\n";
				return 0;
			}
			return 1;
		}
		else
		{
			if (destination.camp != chosen.camp && destination.camp != -999 && end.x - start.x  == 1 && abs(end.y - start.y) == 1)//kill enemy
			{
				destination = chosen;
				chosen = piece();
			}
			else if (chosen.moved && end.x - start.x == 1 && destination.pieceId == null && chosen.camp != destination.camp)//moved
			{
				destination = chosen;
				chosen = piece();
			}
			else if (!chosen.moved && end.x - start.x == 2 && destination.pieceId == null && chosen.camp != destination.camp)
			{
				chosen.moved = true;
				destination = chosen;
				chosen = piece();

			}
			else
			{
				cout << "cant mobve\n";
				return 0;
			}
			return 1;
		}
		
	default:
		return 0;
	}
}
