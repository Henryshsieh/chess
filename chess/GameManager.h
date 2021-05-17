#pragma once
#include "Player.h"
#include <fstream>
#include "Viewer.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
class GameManager
{
public:
	GameManager();
	int run();
	bool isGameOver(Player);
	bool isTie();
	void ProcessInput();
	
	Position start;
	Position end;
private:
	int check;
	int t;
	Player players[2];
	int current_player;
	Board board;
	Viewer viewer;
	int count;
	


};

bool GameManager::isTie()
{
	for (int i = 0 ; i < BOARDLEN ; i ++)
	{
		for (int j = 0 ; j < BOARDLEN ; j++)
		{
			if (board.board[i][j].pieceId != KING && board.board[i][j].pieceId != null)
				return 0;
		}
	}
	cout << "tie\n";
	return 1;
}

void GameManager::ProcessInput()
{
	sf::Event event;
	Position p;
	while (viewer.window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			viewer.window.close();
			exit(0);

		}
	}
	
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			t = 0;
			p.y = event.mouseButton.x / 112.5f;
			p.x = event.mouseButton.y / 112.5f;
			if (!check)
			{
				count++;
				start = p;
				if(count == 1)
					if (board.board[start.x][start.y].pieceId != null)
					{
						current_player = board.board[start.x][start.y].camp;

					}
				board.print(start);
				viewer.movePicture(board, start, players[current_player]);
			}
			else
			{
				end = p;
				if (players[current_player].OnMove(board, start, end))
				{
					players[current_player].OnPromote(board);
					cout << "from" << start.x << " " << start.y << " to" << end.x << " " << end.y << endl;
					current_player ^= 1;
					if (board.isThreatened(players[current_player].findKing(board), players[current_player].camp))
					{
						viewer.showcheck();
						cout << "checkcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheckcheck\n";
					}
					if (isGameOver(players[current_player]))
					{
						exit(0);
					}
					if (isTie())
					{
						exit(0);
					}
				}
				viewer.movePicture(board);
			}
			check = check ^ 1;
		}

		if (event.mouseButton.button == sf::Mouse::Right)
		{
			cout << " player "<< current_player << " surrounded\n";
			exit(0);
		}
	}
	t++;
	if (t == 500)
	{
		cout << " player " << current_player << " lose\n";

		exit(0);
	}
}


int GameManager::run()
{
		
	bool check = 0;
	while (1)
	{
		while (viewer.window.isOpen()) {

			ProcessInput();
			viewer.Display();
		}


	}
	return 0;
}

GameManager::GameManager()
{
	check = 0;
	t = 0;
	count = 0;
	board = Board();
	//viewer = Viewer();
	players[0] = Player(0, board);
	players[1] = Player(1, board);
	current_player = 0;
	start.x = 0;
	start.y = 0;
	end.x = 0;
	end.y = 0;

	
}




bool GameManager::isGameOver(Player player)
{
	Board temp = board;

	if (!board.isThreatened( player.findKing(board), player.camp))
		return 0;
	for (int j = 0; j < BOARDLEN; j++)
	{
		for (int k = 0; k < BOARDLEN; k++)
		{
			if (board.board[j][k].camp == player.camp)
			{
				for (auto element : board.board[j][k].availablemove)
				{
					cout << "               " << j << k << " " << element.x << element.y << endl;
					if (player.OnMove(temp, temp.board[j][k]._position, element))
					{
						return 0;
						temp = board;
					}
				}
			}
		}
	}
	cout << "player " << player.camp << " lose";
	return 1;

}
 