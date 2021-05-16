#pragma once
#include "Player.h"
#include <fstream>
#include "Viewer.h"
class GameManger
{
public:
	GameManger();
	void run();
	bool move(Board& board, Position&, Position&);
	bool isGameOver();
	void refresh();//refresh players' member status
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
		if (!isGameOver())
		{
			cout << "game over";
			break;
		}
		if (current_player == 0)
		{
			players[0].OnMove(board, start, end);
			if (move(board, start, end))
				current_player = 1;
		}
		else
		{
			players[1].OnMove(board, start, end);
			if (move(board, start, end))
				current_player = 0;

		}
		refresh();//refresh players' member status
		board.save();
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


bool GameManger::move(Board& board, Position& start, Position& end)
{
	piece backup_chosen = board.board[start.x][start.y];
	piece& chosen = board.board[start.x][start.y];
	piece backup_destination = board.board[end.x][end.y];
	piece& destination = board.board[end.x][end.y];
	if (chosen.camp == destination.camp || chosen.camp != current_player)//end cant be alley, start cant be enemy
		return 0;
	for (auto element : chosen.availbe)
	{
		if (end.x == element.x && end.y == element.y)
		{
			destination = chosen;
			destination._position = end;
			chosen = piece();
			refresh();
			if (players[current_player].isThreatened(board, players[current_player].king->_position))
			{
				cout << "protect the king!\n";
				destination = backup_destination;
				chosen = backup_chosen;
				return 0;
			}
			else
			{
				switch (destination.pieceId)
				{
				case KING:
					players[current_player].king = &destination;
					return 1;
				case KNIGHT:
					players[current_player].knight[destination.pieceIndex] = &destination;
					return 1;
				case QUEEN:
					players[current_player].queen = &destination;
					return 1;
				case ROOK:
					players[current_player].rook[destination.pieceIndex] = &destination;
					return 1;
				case BISHOP:
					players[current_player].bishop[destination.pieceIndex] = &destination;
					return 1;
				case PAWN:
					players[current_player].pawn[destination.pieceIndex] = &destination;
					return 1;
				default:
					break;
				}
			}
		}
	}
	return 0;
}


void GameManger::refresh()
{
	for (int index = 0 ; index < 2 ; index ++)
	{
		players[index].setAvailablePath(board);
		if (players[index].king != NULL && players[index].king->camp != players[index].camp)
			players[index].king = NULL;
		if (players[index].queen != NULL && players[index].queen->camp != players[index].camp)
		for (int i = 0; i < 2; i++)
		{
			if (players[index].bishop != NULL && players[index].bishop[i]->camp != players[index].camp)
				players[index].bishop[i] = NULL;
			if (players[index].knight[i] != NULL && players[index].knight[i]->camp != players[index].camp)
				players[index].knight[i] = NULL;
			if (players[index].rook[i]->camp != players[index].camp)
				players[index].rook[i] = NULL;
		}
		for (int i = 0; i < 8; i++)
		{
			if (players[index].pawn[i] != NULL && players[index].pawn[i]->camp != players[index].camp)
				players[index].pawn[i] = NULL;
		}

	}
	
}

bool GameManger::isGameOver()
{
	Board temp = board;
	for (int i = 0 ; i < 2 ; i ++)
	{
		if (!players[i].isThreatened(board, players[i].king->_position))
			break;
		for (int j = 0 ; j < BOARDLEN ; j++)
		{
			for (int k = 0 ; k < BOARDLEN ; k++)
			{
				if (board.board[j][k].camp == players[i].camp)
				{
					for (auto element : board.board[j][k].availbe)
					{
						if (move(temp, temp.board[j][k]._position, element))
						{
							if (!players[i].isThreatened(temp, players[i].king->_position))
								return 0;
							temp = board;
						}
					}
				}
			}
		}
	}
	return 1;

}
