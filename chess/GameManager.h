#pragma once
#include "Player.h"
#include "Viewer.h"
class GameManger
{
public:
	GameManger();
	~GameManger();
	void run();
private:
	Player players;
	int current_player;
	Viewer viewer;
	Board board;
};
void GameManger::run()
{
	while (true)
	{
		players.OnMove(board);
	}
}

GameManger::GameManger()
{
	board = Board();
	viewer = Viewer();
	players = Player();
}

GameManger::~GameManger()
{
}
