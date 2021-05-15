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
			if (move(board, start, end))
				current_player = 1;
			players[0].refresh();
		}
		else
		{
			cout << "player1\n";
			players[1].OnMove(board, start, end);
			if (move(board, start, end))
				current_player = 0;
			players[1].refresh();
		}
	}
}

GameManger::GameManger()
{
	board = Board();
	viewer = Viewer();
	players[0] = Player(0,board);
	players[1] = Player(1,board);
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
	if (chosen.camp == destination.camp || chosen.camp != current_player)//end cant be alley, start cant be enemy
		return 0;
	switch (chosen.pieceId)
	{
	case null:
		cout << "null\n";
		return 0;
	case KING:
		if (start.x != end.x || start.y != end.y ) //不是同位置
		{
			if (abs(end.x - start.x) <= 1 && abs(end.y - start.y) <= 1)
			{
				destination = chosen;
				players[current_player].king = &(destination);
				destination._position = end;
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
	case QUEEN:
		if (start.x != end.x || start.y != end.y) //不是同位置
		{
			//同X horizontal
			if (start.x == end.x)
			{
				for (int i = 0,j = 0 ; j < abs(end.y - start.y) - 1 ;j++)
				{
					if (end.y - start.y < 0)
						i--;
					else
						i++;
					if (board.board[start.x][start.y + i].pieceId != null)
					{
						cout << "crossing\n";
						return 0;
					}
					
				}
				players[current_player].queen = &(destination);
				destination = chosen;
				destination._position = end;
				chosen = piece();
			}
			//vertical
			else if (start.y == end.y)
			{
				for (int i = 0, j = 0; j < abs(end.x - start.x) - 1 ; j++)
				{
					if (end.x - start.x < 0)
						i--;
					else
						i++;
					if (board.board[start.x + i][start.y].pieceId != null)
					{
						cout << "crossing\n";
						return 0;
					}
					
				}
				players[current_player].queen = &(destination);
				destination = chosen;
				destination._position = end;
				chosen = piece();
			}
			else if (abs(start.x - end.x) == abs(start.y - end.y)) //斜向
			{
				for (int i = 0, k = 0, j = 0; j < abs(end.y - start.y) - 1 ; j++)
				{
					if (end.y - start.y < 0)
						i--;
					else
						i++;
					if (end.x - start.x < 0)
						k--;
					else
						k++;
					if (board.board[start.x + k][start.y + i].pieceId != null)
					{
						cout << "crossing\n";
						return 0;
					}
					
				}

				players[current_player].queen = &(destination);
				destination = chosen;
				destination._position = end;
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
	case ROOK:

		if (start.x != end.x || start.y != end.y) //不是同位置
		{
			if (start.x == end.x) //同X
			{
				for (int i = 0, j = 0; j < abs(end.y - start.y) - 1; j++)
				{
					if (end.y - start.y < 0)
						i--;
					else
						i++;
					if (board.board[start.x][start.y + i].pieceId != null)
					{
						cout << "crossing\n";
						return 0;
					}

				}
				players[current_player].rook[chosen.pieceIndex] = &(destination);
				destination = chosen;
				destination._position = end;
				chosen = piece();
			}
			else if (start.y == end.y) //同Y
			{
				for (int i = 0, j = 0; j < abs(end.x - start.x) - 1; j++)
				{
					if (end.x - start.x < 0)
						i--;
					else
						i++;
					if (board.board[start.x + i][start.y].pieceId != null)
					{
						cout << "crossing\n";
						return 0;
					}

				}
				players[current_player].rook[chosen.pieceIndex] = &(destination);
				destination = chosen;
				destination._position = end;
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
	case BISHOP:
		if (start.x != end.x || start.y != end.y) //不是同位置
		{
			if (abs(start.x - end.x) == abs(start.y - end.y)) //斜向
			{
				for (int i = 0, k = 0, j = 0; j < abs(end.y - start.y) - 1; j++)
				{
					if (end.y - start.y < 0)
						i--;
					else
						i++;
					if (end.x - start.x < 0)
						k--;
					else
						k++;
					if (board.board[start.x + k][start.y + i].pieceId != null)
					{
						cout << "crossing\n";
						return 0;
					}

				}
				players[current_player].bishop[chosen.pieceIndex] = &(destination);
				destination = chosen;
				destination._position = end;
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
	case KNIGHT:
		if ((abs(start.x - end.x) == 2 && abs(start.y - end.y) == 1) || (abs(start.x - end.x) == 1 && abs(start.y - end.y) == 2)) //日字
		{
			players[current_player].bishop[chosen.pieceIndex] = &(destination);
			destination = chosen;
			destination._position = end;
			chosen = piece();
		}
		else
		{
			cout << "cant move knight\n";
			return 0;
		}
		return 1;
	case PAWN:
		if (current_player == 0)
		{
			if (destination.pieceId != null && start.x - end.x == 1 && abs(start.y - end.y) == 1)
			{
				players[current_player].pawn[chosen.pieceIndex] = &(destination);
				destination = chosen;
				destination._position = end;
				chosen = piece();
			}
			else if (chosen.moved && start.x - end.x == 1 && start.y == end.y && destination.pieceId == null )//moved
			{
				players[current_player].pawn[chosen.pieceIndex] = &(destination);
				destination = chosen;
				destination._position = end;
				chosen = piece();
			}
			else if (!chosen.moved && start.y == end.y && destination.pieceId == null)
			{
				if (start.x - end.x == 1)
				{
					chosen.moved = true;
					players[current_player].pawn[chosen.pieceIndex] = &(destination);
					destination = chosen;
					destination._position = end;
					chosen = piece();
				}
				else if (start.x - end.x == 2)
				{
					chosen.moved = true;
					players[current_player].pawn[chosen.pieceIndex] = &(destination);
					destination = chosen;
					destination._position = end;
					chosen = piece();
				}
			}
			else
			{
				cout << "cant move\n";
				return 0;
			}
			return 1;
		}
		else 
		{
			if (destination.pieceId != null && end.x - start.x == 1 && abs(end.y - start.y) == 1)//kill enemy
			{
				players[current_player].pawn[chosen.pieceIndex] = &(destination);
				destination = chosen;
				destination._position = end;
				chosen = piece();
			}
			else if (chosen.moved && end.x - start.x == 1 && start.y == end.y && destination.pieceId == null )//moved
			{
				players[current_player].pawn[chosen.pieceIndex] = &(destination);
				destination = chosen;
				destination._position = end;
				chosen = piece();
			}
			else if (!chosen.moved && start.y == end.y && destination.pieceId == null )
			{
				players[current_player].pawn[chosen.pieceIndex] = &(destination);
				chosen.moved = true;
				destination = chosen;
				destination._position = end;
				chosen = piece();
			}
			else
			{
				cout << "cant move\n";
				return 0;
			}
			return 1;
		}
		return 1;
	default:
		return 0;
	}
}
