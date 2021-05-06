#pragma once
#include "Player.h"
#include "Viewer.h"
class GameManger
{
public:
	GameManger();
	~GameManger();
private:
	Player* players[2];
	int current_player;
	Viewer viewer;

};

GameManger::GameManger()
{
}

GameManger::~GameManger()
{
}
