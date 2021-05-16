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
	Position start;
	Position end;

private:
	Player players[2];
	int current_player;
	//Viewer viewer;
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
		board.save();
	}
}

GameManger::GameManger()
{
	board = Board();
	//viewer = Viewer();
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
			players[0].setAvailablePath(board);
			players[1].setAvailablePath(board);
			if (players[current_player].isThreatened(board, players[current_player].findKing(board)))
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


bool GameManger::isGameOver()
{
	Board temp = board;
	for (int i = 0 ; i < 2 ; i ++)
	{
		if (!players[i].isThreatened(board, players[current_player].findKing(board)))
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
							if (!players[i].isThreatened(temp, players[current_player].findKing(board)))
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
